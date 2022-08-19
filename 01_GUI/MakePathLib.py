import sys
from pathlib import Path

tree_str = ''


def generate_tree(pathname, n=0, depth=0):
    """
    生成路径树
    :param pathname:    路径
    :param n:           递归标识
    :param depth:       生成深度
    :return:
    """
    global tree_str
    if pathname.is_file():
        tree_str += '    |' * n + '-' * 4 + pathname.name + '\n'
    elif pathname.is_dir():
        tree_str += '    |' * n + '-' * 4 + \
            str(pathname.relative_to(pathname.parent)) + '\\' + '\n'
        for cp in pathname.iterdir():
            if n < depth:
                generate_tree(cp, n + 1, depth=depth)


if __name__ == '__main__':
    if len(sys.argv) > 1:
        for i in range(1, len(sys.argv)):
            if sys.argv[i] == '-depth' or sys.argv[i] == '-d':
                if len(sys.argv) > i + 1:
                    generate_tree(Path(''), depth = int(sys.argv[i + 1]))
    else:
        generate_tree(Path(''), depth = 50)
    with open('PathLib.txt', mode='w') as Fp:
        Fp.write(tree_str)
