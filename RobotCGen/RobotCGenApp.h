/***************************************************************
 * Name:      RobotCGenApp.h
 * Purpose:   Defines Application Class
 * Author:    Adam Whisnant (palidin112@hotmail.com)
 * Created:   2013-07-08
 * Copyright: Adam Whisnant ()
 * License:
 **************************************************************/

#ifndef ROBOTCGENAPP_H
#define ROBOTCGENAPP_H

#include <wx/app.h>

class RobotCGenApp : public wxApp
{
    public:
        virtual bool OnInit();
        void create();
};

#endif // ROBOTCGENAPP_H
