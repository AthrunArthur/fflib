import os

cur_dir = os.path.dirname(os.path.abspath(__file__))
ff_path = os.path.join(cur_dir, '../include/')
lib_path = os.path.join(cur_dir, '../lib/')

def get_all_cpp_files():
    files = []
    for item in os.listdir(cur_dir):
        if item.endswith('.cpp'):
            files.append(os.path.join(cur_dir, item))
    return files

def generate_compile_cmd(fp):
    cxx = os.getenv('CXX')
    if cxx is None or len(cxx) == 0:
        cxx = 'g++'
    cmd = cxx + ' -std=c++11 -I' + ff_path + ' -L' +lib_path
    cmd += ' ' + fp + ' '
    cmd += '-o m' + ' -lmysqlcppconn -lpthread'
    print(cmd)
    return cmd

def compile_all_cpp_files():
    files = get_all_cpp_files()
    for f in files:
        cmd = generate_compile_cmd(f)
        print ('\n\nCompiling ' + f + ' ..........................................')
        os.system(cmd)

if __name__ == '__main__':
    compile_all_cpp_files()

