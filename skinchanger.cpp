//
// Created by toxicoverflow on 23.02.17.
//

#include "skinchanger.h"

std::unordered_map<int, cSkin> cSkinchanger::SkinList = std::unordered_map<int, cSkin>( {
	/* https://github.com/sonicrules11/CSGO-skin-ID-dumper/blob/master/item_index.txt */
	// std::make_pair(WEAPON, cSkin(SKIN, WEAR, KNIFE ONLY, Stattrak, (char*)("Name") or nullptr for no name, FLOAT)),
	// Knife
	std::make_pair(WEAPON_KNIFE, cSkin(414, -1, WEAPON_KNIFE_M9_BAYONET, -1, nullptr, 0.0001f)),
	// Pistols
	std::make_pair(WEAPON_CZ75A, cSkin(-1, -1, -1, -1, nullptr, 0.0001f)),
	std::make_pair(WEAPON_DEAGLE, cSkin(-1, -1, -1, -1, nullptr, 0.0001f)),
	std::make_pair(WEAPON_ELITE, cSkin(-1, -1, -1, -1, nullptr, 0.0001f)),
	std::make_pair(WEAPON_FIVESEVEN, cSkin(-1, -1, -1, -1, nullptr, 0.0001f)),
	std::make_pair(WEAPON_GLOCK, cSkin(-1, -1, -1, -1, nullptr, 0.0001f)),
	std::make_pair(WEAPON_HKP2000, cSkin(-1, -1, -1, -1, nullptr, 0.0001f)), // P2000
	std::make_pair(WEAPON_P250, cSkin(-1, -1, -1, -1, nullptr, 0.0001f)),
	std::make_pair(WEAPON_REVOLVER, cSkin(-1, -1, -1, -1, nullptr, 0.0001f)),
	std::make_pair(WEAPON_TEC9, cSkin(-1, -1, -1, -1, nullptr, 0.0001f)),
	std::make_pair(WEAPON_USP_SILENCER, cSkin(-1, -1, -1, -1, nullptr, 0.0001f)),
	// Rifles
	std::make_pair(WEAPON_KNIFE, cSkin(-1, -1, -1, -1, nullptr, 0.0001f)),
	std::make_pair(WEAPON_KNIFE, cSkin(-1, -1, -1, -1, nullptr, 0.0001f)),
	std::make_pair(WEAPON_KNIFE, cSkin(-1, -1, -1, -1, nullptr, 0.0001f)),
	std::make_pair(WEAPON_KNIFE, cSkin(-1, -1, -1, -1, nullptr, 0.0001f)),
	std::make_pair(WEAPON_KNIFE, cSkin(-1, -1, -1, -1, nullptr, 0.0001f)),
	std::make_pair(WEAPON_KNIFE, cSkin(-1, -1, -1, -1, nullptr, 0.0001f)),
	std::make_pair(WEAPON_KNIFE, cSkin(-1, -1, -1, -1, nullptr, 0.0001f)),
	std::make_pair(WEAPON_KNIFE, cSkin(-1, -1, -1, -1, nullptr, 0.0001f)),
	std::make_pair(WEAPON_KNIFE, cSkin(-1, -1, -1, -1, nullptr, 0.0001f)),
	std::make_pair(WEAPON_KNIFE, cSkin(-1, -1, -1, -1, nullptr, 0.0001f)),
	std::make_pair(WEAPON_KNIFE, cSkin(-1, -1, -1, -1, nullptr, 0.0001f)),
	// SMGs
	std::make_pair(WEAPON_KNIFE, cSkin(-1, -1, -1, -1, nullptr, 0.0001f)),
	std::make_pair(WEAPON_KNIFE, cSkin(-1, -1, -1, -1, nullptr, 0.0001f)),
	std::make_pair(WEAPON_KNIFE, cSkin(-1, -1, -1, -1, nullptr, 0.0001f)),
	std::make_pair(WEAPON_KNIFE, cSkin(-1, -1, -1, -1, nullptr, 0.0001f)),
	std::make_pair(WEAPON_KNIFE, cSkin(-1, -1, -1, -1, nullptr, 0.0001f)),
	std::make_pair(WEAPON_KNIFE, cSkin(-1, -1, -1, -1, nullptr, 0.0001f)),
	// Heavy
	std::make_pair(WEAPON_KNIFE, cSkin(-1, -1, -1, -1, nullptr, 0.0001f)),
	std::make_pair(WEAPON_KNIFE, cSkin(-1, -1, -1, -1, nullptr, 0.0001f)),
	std::make_pair(WEAPON_KNIFE, cSkin(-1, -1, -1, -1, nullptr, 0.0001f)),
	std::make_pair(WEAPON_KNIFE, cSkin(-1, -1, -1, -1, nullptr, 0.0001f)),
	std::make_pair(WEAPON_KNIFE, cSkin(-1, -1, -1, -1, nullptr, 0.0001f)),
	std::make_pair(WEAPON_KNIFE, cSkin(-1, -1, -1, -1, nullptr, 0.0001f)),	
} );

std::unordered_map<int, const char*> cSkinchanger::ModelList;

cSkinchanger* skinchanger = new cSkinchanger;

void cSkinchanger::FrameStageNotify(ClientFrameStage_t stage) {
    if(stage == FRAME_NET_UPDATE_POSTDATAUPDATE_START){
        pLocalPlayer = (C_BaseEntity*)(pEntList->GetClientEntity(pEngine->GetLocalPlayer()));

        if(pLocalPlayer && pLocalPlayer->GetHealth() > 0){
            if(!bInit){
                Init();
                bInit = true;
            }

            ForceSkins();
        }
    }
}

void cSkinchanger::FindModels() {
    ModelList[pModelInfo->GetModelIndex("models/weapons/v_knife_default_ct.mdl")] = KnifeToModelMatrix[Knife].c_str();
    ModelList[pModelInfo->GetModelIndex("models/weapons/v_knife_default_t.mdl")] = KnifeToModelMatrix[Knife].c_str();
}

void cSkinchanger::ForceSkins() {
    IEngineClient::player_info_t player_info;

    if(pEngine->GetPlayerInfo(pLocalPlayer->GetId(), &player_info)){

        int* pWeapons = pLocalPlayer->GetWeapons();

        C_BaseViewModel* LocalPlayerViewModel = (C_BaseViewModel*)pEntList->GetClientEntityFromHandle(pLocalPlayer->GetViewModel());

            C_BaseAttributableItem* WeaponViewModel = nullptr;

        if(LocalPlayerViewModel)
            WeaponViewModel = (C_BaseAttributableItem*)pEntList->GetClientEntityFromHandle(LocalPlayerViewModel->GetWeapon());

        C_BaseCombatWeapon* localWeapon = (C_BaseCombatWeapon*)pEntList->GetClientEntityFromHandle(pLocalPlayer->GetActiveWeapon());

        if(pWeapons){
            for(int i = 0; pWeapons[i]; i++){
                C_BaseAttributableItem* attributableItem = (C_BaseAttributableItem*)pEntList->GetClientEntityFromHandle(pWeapons[i]);

                if(attributableItem){
                    int* Definition = attributableItem->GetItemDefinitionIndex();

                    std::unordered_map<int, cSkin>::iterator SkinIter = (*Definition == WEAPON_KNIFE_T ? SkinList.find(WEAPON_KNIFE) : SkinList.find(*Definition));

                    if(SkinIter != SkinList.end()) {
                        if(*attributableItem->GetOriginalOwnerXuidLow() == player_info.xuidlow && *attributableItem->GetOriginalOwnerXuidHigh() == player_info.xuidhigh){

                            int* model_index = attributableItem->GetModelIndex();

                            std::unordered_map<int, const char*>::iterator model_iter = ModelList.find(*model_index);

                            if(model_iter != ModelList.end()){
                                *model_index = pModelInfo->GetModelIndex(model_iter->second);
                            }

                            cSkin skin = std::move(SkinIter->second);

                            if(Knife && (*Definition == WEAPON_KNIFE || *Definition == WEAPON_KNIFE_T))
                                *attributableItem->GetItemDefinitionIndex() = Knife;


                            if(skin.name){
                                sprintf(attributableItem->GetCustomName(), skin.name);
                            }

                            *attributableItem->GetItemIDHigh() = -1;
                            *attributableItem->GetFallbackPaintKit() = skin.Paintkit;
                            *attributableItem->GetFallbackStatTrak() = skin.StatTrack;
                            *attributableItem->GetEntityQuality() = 4;
                            *attributableItem->GetFallbackSeed() = skin.Seed;
                            *attributableItem->GetFallbackWear() = skin.Wear;
                            *attributableItem->GetAccountID() = player_info.xuidlow;
                        }
                    }

                    if (WeaponViewModel && WeaponViewModel == attributableItem)
                    {
                        int* model_index = ((C_BaseEntity*)LocalPlayerViewModel)->GetModelIndex();

                        std::unordered_map<int, const char*>::iterator model_iter = ModelList.find(*model_index);

                        if (model_iter != ModelList.end())
                        {
                            *model_index = pModelInfo->GetModelIndex(model_iter->second);
                        }
                    }

                }
            }

            if(LocalPlayerViewModel && localWeapon){

                int* model_index = ((C_BaseEntity*)LocalPlayerViewModel)->GetModelIndex();

                std::unordered_map<int, const char*>::iterator model_iter = ModelList.find(*((C_BaseEntity*)localWeapon)->GetModelIndex());

                if(model_iter != ModelList.end()){
                    *model_index = pModelInfo->GetModelIndex(model_iter->second);
                }
            }
        }
    }
}

void cSkinchanger::Init() {
    ModelList.clear();
    FindModels();
}

void cSkinchanger::FireEventClientSide(IGameEvent *event) {

    if (!strcmp(event->GetName(), "game_newmap"))
    {
        Init();
    }
}