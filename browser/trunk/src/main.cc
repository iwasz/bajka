/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <Shell.h>
#include <Bajka.h>
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/variables_map.hpp>
#include <boost/program_options/cmdline.hpp>
#include <boost/program_options/parsers.hpp>
#include <string>
#include "DebugButtonController.h"
#include "ReloadableXmlModelManager.h"
#include "SceneController.h"
#include "GLESWidget.h"

namespace po = boost::program_options;

int main (int argc, char **argv)
{
        Util::ShellConfig config;

        // Declare the supported options.
        po::options_description desc("Allowed options");
        desc.add_options()
                ("help,h", "produce help message")
                ("fullscreen,f", "run in full screen mode")
                ("showaabb,a", "show AABBs around objects")
                ("viewportWidth,x", po::value<int>(&config.viewportWidth), "set horizontal resolution in pixels")
                ("viewportHeight,y", po::value<int>(&config.viewportHeight), "set vertical resolution in pixels")
                ("loopdelay,l", po::value<int>(&config.loopDelayMs), "set game loop delay in ms")
                ("definition,d", po::value <std::string>(&config.definitionFile)->default_value ("main.xml"), "input file with XML definitions");

        po::positional_options_description p;
        p.add ("definition", -1);

        po::variables_map vm;
        po::store(po::command_line_parser(argc, argv).options(desc).positional(p).run(), vm);
        po::notify(vm);

        if (vm.count("help")) {
            std::cout << desc << "\n";
            return 1;
        }

        config.fullScreen = vm.count ("fullscreen");
        config.showAABB = vm.count ("showaabb");

        Shell *shell = Shell::instance ();
        return shell->run (config);
}


