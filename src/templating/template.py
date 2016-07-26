from template_snippets import *
from os.path import join
import sys
import argparse
from jinja2 import Environment, FileSystemLoader


def get_parameters():
    parser = argparse.ArgumentParser()

    parser.add_argument("-i", "--id", dest="cnn_id", help="Name of the CNN")
    parser.add_argument("-a", "--arch", dest="cnn", help="cnn architecture")
    parser.add_argument("-tr", "--train", dest="train", help="train dataset")
    parser.add_argument("-ts", "--test", dest="test", help="test dataset")
    args = parser.parse_args()

    return args.cnn_id, args.cnn, args.train, args.test


def write_cnn(template_path, instantiated_values, output_dir='.'):
    j2_env = Environment(loader=FileSystemLoader(template_path),
                         trim_blocks=True)
    # Instantiate the template with the desired values
    instantiated_cnn = j2_env.get_template('template.net').render(instantiated_values)
    # Write the new network
    with open(join(output_dir, instantiated_values['cnn_id'] + '.net'), 'w') as cnn_file:
        cnn_file.write(instantiated_cnn)


def populate_snippet(snippet, values):
    # Create the jinja2 environment.
    j2_env = Environment(trim_blocks=True)
    return j2_env.from_string(snippet).render(values)


def instantiate_params(parameters, layer_type, values_instantiate):
    for key, param in zip(snippets[layer_type]['values'], parameters):
        values_instantiate[key] = param
    snippet_value = populate_snippet(snippets[layer_type]['template'],
                                     values_instantiate)
    return snippet_value


def append_multilayer(snippet_layer, snippet_value, values_cnn):
    if snippet_layer not in values_cnn.keys():
        values_cnn[snippet_layer] = [snippet_value]
    else:
        values_cnn[snippet_layer].append(snippet_value)


def instantiate_conv(num_conv, parameters, values_cnn):
    values_instantiate = {}
    # Layers that may be repeated must have different ids
    # Set layer name
    num_conv += 1
    layer_id = 'conv_' + str(num_conv)
    values_instantiate['conv_id'] = layer_id

    # Instantiate the parameters
    if '_' in parameters:
        parameters, pad_parameters = parameters.split('_')
        pad_parameters = [param for param in pad_parameters.split('x') if param]

        # Same value for row padding and column padding
        if len(pad_parameters) == 1:
            pad_parameters.append(pad_parameters[0])
            # TODO Do it in a log
            print('Assuming the same value for row padding and column padding')
        # Evaluate if the syntax for the padding is correct.
        if len(pad_parameters) != 2:
            sys.exit('Invalid number of padding values.')

        pad_values = {'rpad': pad_parameters[0],
                      'cpad': pad_parameters[1]}
        values_instantiate['rpad_cpad'] = populate_snippet(snippets['rpad_cpad']['template'],
                                           pad_values)

    parameters = [param for param in parameters.split('x') if param]
    # Same value for row and column filter size
    if len(parameters) == 2:
        parameters.append(parameters[1])
        # TODO Do it in a log
        print('Assuming the same value for row and column filter size.')
    # Evaluate if the syntax is correct.
    if len(parameters) != 3:
        sys.exit('Invalid number of parameters in the convolutional layer.')

    snippet_value = instantiate_params(parameters, 'c', values_instantiate)

    snippet_layer = snippets_to_template['c']
    append_multilayer(snippet_layer, snippet_value, values_cnn)

    return num_conv, layer_id


def instantiate_hidden(num_fh, parameters, values_cnn):
    values_instantiate = {}
    # Layers that may be repeated must have different ids
    # Set layer name
    num_fh += 1
    layer_id = 'fh_' + str(num_fh)
    values_instantiate['fh_id'] = layer_id

    parameters = [param for param in parameters.split('x') if param]
    if len(parameters) != 1:
        sys.exit('Invalid number of parameters in the hidden layer.')
    snippet_value = instantiate_params(parameters, 'fh', values_instantiate)

    snippet_layer = snippets_to_template['fh']
    append_multilayer(snippet_layer, snippet_value, values_cnn)

    return num_fh, layer_id


def instantiate_mp(num_mp, parameters, values_cnn):
    values_instantiate = {}
    # Layers that may be repeated must have different ids
    # Set layer name
    num_mp += 1
    layer_id = 'mp_' + str(num_mp)
    values_instantiate['mp_id'] = layer_id

    parameters = [param for param in parameters.split('x') if param]
    # Same value for row and column max pooling layer
    if len(parameters) == 1:
        parameters.append(parameters[0])
        # TODO Do it in a log
        print('Assuming the same value for row and column max pooling layer.')
    # Evaluate if the syntax is correct.
    if len(parameters) != 2:
        sys.exit('Invalid number of parameters in the max pooling layer.')
    snippet_value = instantiate_params(parameters, 'mp', values_instantiate)

    snippet_layer = snippets_to_template['mp']
    append_multilayer(snippet_layer, snippet_value, values_cnn)

    return num_mp, layer_id


def instantiate_layer(layer_type, parameters, values_cnn):
    values_instantiate = {}
    parameters = parameters.split('x')
    layer_id = None
    if layer_type == 'ci':
        layer_id = 'in'
        # Evaluate if the syntax is correct.
        if len(parameters) != 3:
            sys.exit('Invalid number of parameters in the input layer.')
    elif layer_type == 'fo':
        # Evaluate if the syntax is correct.
        if len(parameters) != 1:
            sys.exit('Invalid number of parameters in the output layer.')
        if not(parameters[0] == 'regression' or parameters[0] == 'classification'):
            sys.exit('Only regression or classification problems')
        layer_id = 'fo'
    else:
        layer_id = layer_type

    # Instantiate the parameters of this layer and save the snippet
    snippet_layer = snippets_to_template[layer_type]
    values_cnn[snippet_layer] = instantiate_params(parameters, layer_type,
                                                   values_instantiate)

    return layer_id


def instantiate_cnn(cnn_name, cnn, train_data, test_data, template_dir=TEMPLATE_DIR):
    values_cnn = {'cnn_id': cnn_name, 'train_data': train_data,
                  'test_data': test_data, 'connections': []}

    old_layer = None
    num_conv, num_mp, num_fh = 0, 0, 0
    non_default_layers = ['ci', 'c', 'mp', 'fh', 'fo']
    for layer in cnn.split('->'):

        # Get the parameters for non default layers
        if '(' in layer:
            layer_type, parameters = layer.split('(')
            values_instantiate = {}

            parameters = parameters[:-1]

            if layer_type == 'c':
                num_conv, layer_id = instantiate_conv(num_conv, parameters,
                                                      values_cnn)
            elif layer_type == 'mp':
                num_mp, layer_id = instantiate_mp(num_mp, parameters, values_cnn)
            elif layer_type == 'fh':
                num_fh, layer_id = instantiate_hidden(num_fh, parameters, values_cnn)
            else:
                layer_id = instantiate_layer(layer_type, parameters, values_cnn)

        # Layers without parameters
        elif layer not in non_default_layers:
            layer_id = layer

        else:
            raise ValueError('Layer {} should have parameters'.format(layer))

        # Instantiate the connections
        if not old_layer:
            old_layer = layer_id
        else:
            values_instantiate = {'pr_layer': old_layer,
                                  'curr_layer': layer_id}
            new_connection = populate_snippet(snippets['connections']['template'],
                                              values_instantiate)
            values_cnn['connections'].append(new_connection)
            old_layer = layer_id

    write_cnn(TEMPLATE_DIR, values_cnn)

if __name__ == '__main__':

    cnn_name, cnn, train_data, test_data = get_parameters()
    instantiate_cnn(cnn_name, cnn, train_data, test_data)
