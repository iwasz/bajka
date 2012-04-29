///****************************************************************************
// *                                                                          *
// *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
// *  ~~~~~~~~                                                                *
// *  License : see COPYING file for details.                                 *
// *  ~~~~~~~~~                                                               *
// ****************************************************************************/
//
//#ifdef ANDROID
//#include "ResourceManager.h"
//#include <boost/make_shared.hpp>
//#include <android_native_app_glue.h>
//#include <android/asset_manager.h>
//
//namespace View {
//
//Ptr <std::string> ResourceManager::getText (std::string const &id) const
//{
//        Ptr <std::string> ret = boost::make_shared <std::string> ();
//
//        AAsset *asset = AAssetManager_open (assetManager, id.c_str (), AASSET_MODE_UNKNOWN);
//
//        int bytesRead;
//        char buffer[BUFSIZ];
//        while ((bytesRead = AAsset_read (asset, buffer, BUFSIZ))) {
//                ret->operator += (buffer);
//        }
//
//        return ret;
//}
//
//} /* namespace View */
//
//#endif
