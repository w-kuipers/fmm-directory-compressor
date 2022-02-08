import sys

sys.path.insert(0, '../build/Debug')

from generate_directory import generate_file_from_path

generate_file_from_path('Z:/01_PROJECTS/192755_Toneelgroep-Oostpool/2112130_Toneelgroep-Oostpool_Edward-II-Interviews', 'Pythontest', './pythonTests/')

# generate('pythonMappie', 'generated_test.json', './pythonTests/')