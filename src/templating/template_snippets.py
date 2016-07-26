from os.path import dirname, abspath
from collections import OrderedDict

TEMPLATE_DIR = dirname(abspath(__file__))

snippets = {'ci': {'template': 'CI in [nz={{ nz }}, nr={{ nr }}, nc={{ nc }}]',
                   'values': OrderedDict.fromkeys(['nz', 'nr', 'nc'])},
            'c': {'template': 'C {{ conv_id }} '
                              '[nk={{ num_filters }}, kr={{ filter_size_rows }}, '
                              'kc={{ filter_size_columns }} {{ rpad_cpad }}]',
                  'values': OrderedDict.fromkeys(['num_filters',
                                                  'filter_size_rows',
                                                  'filter_size_columns'])},
            'fh': {'template': 'F  {{ fh_id }} [numnodes={{ fc_hidden_nodes }}]',
                   'values': OrderedDict.fromkeys(['fc_hidden_nodes'])},
            'mp': {'template': 'MP {{ mp_id }} [sizer={{ rows }}, '
                               'sizec={{ columns }}]',
                   'values': OrderedDict.fromkeys(['rows', 'columns'])},
            'fo': {'template': 'FO fo [{{ problem_type }}]',
                   'values':OrderedDict.fromkeys(['problem_type'])},
            'connections': {'template': '{{ pr_layer }}->{{ curr_layer }}'},
            'rpad_cpad':{'template': ', rpad={{ rpad }}, cpad={{ cpad }}',
                         'values': OrderedDict.fromkeys(['rpad', 'cpad'])}
            }

snippets_to_template = {'ci': 'c_in',
                        'c': 'conv_layers',
                        'mp': 'mp_layers',
                        'fh': 'fh_layers',
                        'fo': 'fo_layer'}
