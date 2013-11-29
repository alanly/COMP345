#include "MapList.h"


MapList::MapList(LoaderParameters* parameters) : GameObject(parameters)
{
	loadTextures();
	gotIt = false;
	map = new Map(10,10);
}


MapList::~MapList(void)
{
}

void MapList::loadTextures() {
	TextureManager::getInstance()->load("img/game/ui/map_load.png", "UI_Map_List", Game::getInstance()->getRenderer());
}

void MapList::draw(){
	TextureManager::getInstance()->draw(new LoaderParameters(0, 0, Game::getInstance()->getWindowWidth(), Game::getInstance()->getWindowHeight(), 0, 0, "UI_Map_List"), Game::getInstance()->getRenderer());


	string curr_directory = "sav\\map\\";
	string extension = "xml";

	if(!gotIt){
		int currentX = 60;
		int currentY = 200;
		int incrementX = 10;
		int incrementY = 35;
		gotIt = true;
		DIR* dir_point = opendir(curr_directory.c_str());
        dirent* entry = readdir(dir_point);
        while (entry) { // if !entry then end of directory
               if (entry->d_type == DT_REG) { // if entry is a regular file
                   std::string fname = entry->d_name; // filename
                   // if filename's last characters are extension
                   if (fname.find(extension, (fname.length() - extension.length())) != std::string::npos) {
					   // add filename to results vector
					   maps.push_back(new GameObject(new LoaderParameters(currentX, currentY, 300, 25, 0, 0, fname.substr(0, fname.length()-4))));
					   currentY += incrementY;
					   currentX += incrementX;
				   }
                }
                entry = readdir(dir_point);
        }
        loadSaveFiles();
	}
	drawSaveFiles();
}


void MapList::loadSaveFiles()
{
	for(vector<GameObject*>::const_iterator iter = maps.begin(); iter != maps.end(); ++iter)
    {
        if(*iter != 0)
        {
            TextureManager::getInstance()->loadFont((*iter)->getParameters()->getId(),Game::getInstance()->getRenderer(), (*iter)->getParameters()->getId());
        }
    }
}

void MapList::drawSaveFiles()
{
	for(vector<GameObject*>::const_iterator iter = maps.begin(); iter != maps.end(); ++iter)
    {
        if(*iter != 0)
        {
            (*iter)->draw();
        }
    }
}
void MapList::handleEvents(){
	for(vector<GameObject*>::const_iterator iter = maps.begin(); iter != maps.end(); ++iter)
    {
        if(*iter != 0)
        {
            (*iter)->handleEvents();
			if((*iter)->isClicked())
			{
				(*iter)->resetClicked();
				//cout << (*iter)->getParameters()->getId() << " will be loaded change view to game view with new character" << endl;
				string filename = (*iter)->getParameters()->getId() + ".xml";
				map = map->readFromFile(filename);
				if(map != nullptr)
				{	
					Game::getInstance()->setCurrentView(enumUtility::Game_Main);
				}else{
					cout << "Map is null " << endl;
				}
				
			}
        }
    }
}
Map* MapList::getMap(){
	return this->map;
}