/***************************************************************
 * Name:      RobotCGenApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Adam Whisnant (palidin112@hotmail.com)
 * Created:   2013-07-08
 * Copyright: Adam Whisnant ()
 * License:
 **************************************************************/

#include "RobotCGenApp.h"

//(*AppHeaders
#include "RobotCGenMain.h"
#include <wx/image.h>
//*)

#include <wx/textdlg.h>


IMPLEMENT_APP(RobotCGenApp);

bool RobotCGenApp::OnInit()
{
    setup();
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if(wxsOK)
    {
        create();
    }
    //*)
    return wxsOK;
}

void RobotCGenApp::create(){
    RobotCGenFrame* Frame = new RobotCGenFrame(0);
    Frame->Show();
    SetTopWindow(Frame);
}
