import sys

sys.path.insert(0, '../build')

from generate_directory import generate

generate('pythonMappie', 'test.json')

def generateDirectoryStructure(self):

        #### Create the main directory....
        try:
            os.mkdir(self.fullProjectPath)
        except Exception as e:
            log.exception(e, 'Unable to create the project directory due to the following exception')
        else:
            log.info('A project directory has been created: "{}"'.format(self.fullProjectPath))
            self.parent.progressBar.progress(5)

        #### Read the structures.xml file....
        self.structuresXML = getResource.properties('structures.xml')
        self.structureData = ET.parse(self.structuresXML)
        self.structureRoot = self.structureData.getroot()
        self.parent.progressBar.progress(1)

        #### Get selected structure....
        selectedStructure = self.structureRoot.find('.//*[@structureID="' + self.structure + '"]')
        self.parent.progressBar.progress(1)
        
        #### Create a list with al depths and get the highest value....
        depths = []
        for elem in selectedStructure.iter():
            if not elem.tag == 'structure':
                depths.append(elem.attrib['depth'])
        deepest = max(depths)

        #### Set variable for assets path....
        assetsPath = os.path.join(getResource.path('properties/structure_assets/'), self.structure)

        #### Get projectdata from the database....
        projectData = databaseHandler.select('all', 'FA_projectbase WHERE project_id = ' + self.projectNumber)
        
        #### Generate all directories in structure tree....
        namingVariablesFunction = namingVariables()
        loop = 0
        while int(deepest) > loop:
            
            for elem in selectedStructure.findall('.//*[@depth="' + str(loop) + '"]'):

                #### Only use directory elements....
                if not elem.tag == 'file' and not elem.tag == 'structure':
                    if elem.attrib['path'] == '':
                        os.mkdir(os.path.join(self.fullProjectPath, elem.attrib['name']))
                    else:
                        os.mkdir(os.path.join(os.path.join(self.fullProjectPath, elem.attrib['path'][1:]), elem.attrib['name']))
                
                if elem.tag == 'file':
                    if elem.attrib['rename'] == 'None':
                        copyfile(os.path.join(assetsPath, elem.attrib['fileID']), os.path.join(self.fullProjectPath, elem.attrib['path'][1:], elem.attrib['name']))
                    else:

                        #### If the file has a rename, we must convert the variables into the actual value....
                        parts = elem.attrib['rename'].split(',')

                        newFileName = ''

                        for part in parts:
                            if namingVariablesFunction.isVar(part):
                                newFileName += namingVariablesFunction.getValue(part, projectData)
                            else:
                                newFileName += part

                        newFileNameWithExtension = newFileName + os.path.splitext(elem.attrib['name'])[1]

                        #### Copy the file with the new file name....
                        copyfile(os.path.join(assetsPath, elem.attrib['fileID']), os.path.join(self.fullProjectPath, elem.attrib['path'][1:], newFileNameWithExtension))
            
            loop += 1
        self.parent.progressBar.progress(10)
