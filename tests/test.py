import sys

sys.path.insert(0, '../build')

from generate_directory import generate

generate('pythonMappie', 'test.json')
