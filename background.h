
//{{BLOCK(levelBG)

//======================================================================
//
//	levelBG, 128x64@8, 
//	Transparent palette entry: 2.
//	+ palette 256 entries, not compressed
//	+ 128 tiles not compressed
//	Total size: 512 + 8192 = 8704
//
//	Time-stamp: 2014-03-03, 22:16:35
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.6
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_LEVELBG_H
#define GRIT_LEVELBG_H

#define backgroundTilesLen 8192
extern const unsigned short backgroundTiles[4096];

#define backgroundPalLen 512
extern const unsigned short backgroundPal[256];

#define menuBGPalLen 512
extern const unsigned short menuBGPal[256];

#define girderMapLen 1024
extern const int girderMap[1024];

#define fenceBGMapLen 1024
extern const int fenceBGMap[1024];

#define buildingBGMapLen 1024
extern const int buildingBGMap[1024];

#define cloudBGMapLen 1024
extern const int cloudBGMap[1024];

#endif // GRIT_LEVELBG_H

//}}BLOCK(levelBG)
