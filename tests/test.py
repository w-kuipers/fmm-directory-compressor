import sys

sys.path.insert(0, '../build')

from generate_directory import generate_file_from_path, generate_structure_from_file

# generate_file_from_path('/home/wibo/Documents/PROTO', 'Pythontest', './pythonTests/', True)

generate_structure_from_file('pythonMappie', 'pythonTests/Pythontest.fps', './pythonTests/')