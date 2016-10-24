#ifndef RF_ASSET_LIST_H
#define RF_ASSET_LIST_H

#include "rf_asset.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include <dirent.h>
#include <vector>
#include <string>
using namespace std;

class RF_Asset_List
{
    public:
        RF_Asset_List(string path);
        virtual ~RF_Asset_List(){}

        string id;
        vector<RF_Asset*> assets;

    private:
        int asset_type(string ext);
        string getConfig(string file);
        vector<string> cfg;
};

#endif // RF_ASSET_LIST_H
