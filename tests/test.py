import sys

sys.path.insert(0, '../build/Debug')

from generate_directory import generate_file_from_path, generate_structure_from_file

# generate_file_from_path('Z:/01_PROJECTS\FILMAGE-DIRSTRUCTURE-TEMPLATE', 'Pythontest', './pythonTests/', True)

generate_structure_from_file('pythonMappie', 'pythonTests/Pythontest.fps', './pythonTests/')