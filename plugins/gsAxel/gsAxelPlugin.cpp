/** @file gsAxelPlugin.h

    @brief This file provides declaration of the G+Smo plugin for Axel modeler.

    This file is part of the G+Smo library. 

    This Source Code Form is subject to the terms of the Mozilla Public
    License, v. 2.0. If a copy of the MPL was not distributed with this
    file, You can obtain one at http://mozilla.org/MPL/2.0/.
    
    Author(s): A. Mantzaflaris
*/
// CAUTION: Undefined functions cause the plugin not to load

#include "gsAxelPlugin.h"

#include "gsGeometryData.h"
#include "gsBasisData.h"
#include "gsMultiPatchData.h"
#include "gsGeometryCreator.h"
#include "gsGeometryDialog.h"
#include "gsReaderXml.h"

//#include "gsGeometryConverter.h"// Using an actor instead

//#include "gsPdeAssembler.h"
//#include "gsPdeAssemblerDialog.h"

#include "gsBasisData.h"
#include "gsBasisConverter.h"

#include <axlGui/axlInspectorObjectFactory.h>
#include <dtkCoreSupport/dtkAbstractDataFactory.h>
#include <dtkCoreSupport/dtkAbstractProcessFactory.h>
#include <dtkLog/dtkLog.h>

// /////////////////////////////////////////////////////////////////
// gsAxelPluginPrivate
// /////////////////////////////////////////////////////////////////

class gsAxelPluginPrivate 
{
public:
    // Class variables go here.
};

// /////////////////////////////////////////////////////////////////
// gsAxelPlugin
// /////////////////////////////////////////////////////////////////

gsAxelPlugin::gsAxelPlugin(QObject *parent) : dtkPlugin(parent), d(new gsAxelPluginPrivate)
{

}

gsAxelPlugin::~gsAxelPlugin(void)
{
    delete d;
    d = NULL;
}

bool gsAxelPlugin::initialize(void)
{
    dtkWarn() << "Warnings are on.\n";

    gsAxelPlugin::dataFactSingleton    = dtkAbstractDataFactory::instance();
    gsAxelPlugin::processFactSingleton = dtkAbstractProcessFactory::instance();
        
    if(!gsGeometryData< axlAbstractCurveBSpline >::registered())
    std::cout << "Unable to register gsGeometryData CURVE type";

    if(!gsGeometryData< axlAbstractSurfaceBSpline >::registered())
	std::cout << "Unable to register gsGeometryData SURFACE type";

    if(!gsGeometryData< axlAbstractVolumeBSpline >::registered())
	std::cout << "Unable to register gsGeometryData VOLUME type";

    if(!gsGeometryData< axlAbstractSurfaceTrimmed >::registered())
	std::cout << "Unable to register gsGeometryData TRIMMED type";

    if(!gsGeometryDialog::registered())
	std::cout  << "Unable to register gsGeometryDialog type";
    
    if(!gsGeometryCreator::registered())
	std::cout << "Unable to register gsGeometryCreator type";

    if(!gsReaderXml::registered())
	std::cout << "Unable to register gsReaderXml type";

    if(!gsBasisData::registered())
    	std::cout << "Unable to register gsBasisData";
    
    if(!gsBasisConverter::registered())
        std::cout << "Unable to register gsBasisConverter";

    if(!gsMultiPatchData::registered())
    	std::cout << "Unable to register gsMultiPatchData";
    
    // if(!gsGeometryWriter::registered())
    //     dtkWarn() << "Unable to register gsGeometryWriter type";    

    std::cout << "G+Smo Plugin for Axel is loaded.\n";
    return true;
}

bool gsAxelPlugin::uninitialize(void)
{
    return true;
}

QString gsAxelPlugin::name(void) const
{
    return "gsAxelPlugin";
}

QString gsAxelPlugin::description(void) const
{
    return "G+Smo plugin. Geometry + Simulation modules, www.gs.jku.at";
}

QStringList gsAxelPlugin::tags(void) const
{
    return QStringList();
}

QStringList gsAxelPlugin::types(void) const
{
    QStringList stringList;
    stringList <<"gsGeometryData"<<"gsGeometryDialog"<<"gsGeometryCreator"
               <<"gsBasisData"   <<"gsBasisConverter"<<"gsMultiPatchData" 
               <<"gsReaderXml";
    return stringList;
}

dtkAbstractDataFactory *gsAxelPlugin::dataFactSingleton = NULL;
dtkAbstractProcessFactory *gsAxelPlugin::processFactSingleton = NULL;


// following line for Qt4 only
//Q_EXPORT_PLUGIN2(gsAxelPlugin, gsAxelPlugin)

