def print_function(proto, args, name):
    typedef = '{0}_t'.format(name)
    ret_type = ' '.join(proto)
    arg_proto = list()
    arg_name = list()
    if len(args) > 0:
        for arg in args:
            arg_tokens = arg.split()
            arg_proto += [' '.join(arg_tokens[:-1])]
            arg_name += list() if len(arg_tokens) == 1 else [arg_tokens[-1]]
    ret = '' if ret_type == 'void' else 'return '
    print 'ATTRIB'
    print '{0} APIENTRY {2}({1}) {{'.format(' '.join(proto), ', '.join(args), name)
#    print '    typedef {0} (WINAPI * {1})({2});'.format(ret_type, typedef, ', '.join(arg_proto))
#    print '    {0} thunk = ({0})gl_func_table[e_{1}];'.format(typedef, name)
#    print '    assert(thunk);'
#    print '    {0}thunk({1});'.format(ret, ', '.join(arg_name))
    print '}'
    print ''


g_func_names = []



def parse(line):
    global g_func_names
    lparen = line.find('(')
    rparen = line.find(')')
    arg = line[lparen+1:rparen]
    arg_tokens = arg.split(',')
    arg_tokens = list(x.strip() for x in arg_tokens)
    proto = line[0:lparen].strip()
    proto_tokens = proto.split()
    proto_tokens = list(x.strip() for x in proto_tokens)
    func_name = proto_tokens[-1]
    print_function(proto_tokens[:-1], arg_tokens, func_name)
    g_func_names += [func_name]


def main():
    with open('glfuncs.txt', 'rb') as f:
        for line in f.readlines():
            parse(line.strip('\r\n'))

    print 'const char *gl_func_names[e_gl_func_count__] = {'
    for x in g_func_names:
        print '    "{0}",'.format(x)
    print '};'
    print ''
    print 'enum gl_func_enum_t {'
    for x in g_func_names:
        print '    e_{0},'.format(x)
    print '    e_gl_func_count__'
    print '};'

if __name__ == '__main__':
    main()
