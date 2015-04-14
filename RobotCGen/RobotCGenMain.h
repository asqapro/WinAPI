/***************************************************************
 * Name:      RobotCGenMain.h
 * Purpose:   Defines Application Frame
 * Author:    Adam Whisnant (palidin112@hotmail.com)
 * Created:   2013-07-08
 * Copyright: Adam Whisnant ()
 * License:
 **************************************************************/

#ifndef ROBOTCGENMAIN_H
#define ROBOTCGENMAIN_H

//(*Headers(RobotCGenFrame)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/spinctrl.h>
#include <wx/slider.h>
#include <wx/panel.h>
#include <wx/choice.h>
#include <wx/button.h>
#include <wx/frame.h>
//*)

class RobotCGenFrame: public wxFrame
{
    public:

        RobotCGenFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~RobotCGenFrame();

    private:

        //(*Handlers(RobotCGenFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnTextCtrl1Text(wxCommandEvent& event);
        void OnRadioButton1Select(wxCommandEvent& event);
        void OnTextCtrl1Text2(wxCommandEvent& event);
        void OnButton1Click(wxCommandEvent& event);
        void OnTextCtrl1Text3(wxCommandEvent& event);
        void OnTextCtrl3Text(wxCommandEvent& event);
        void OnTextCtrl2Text(wxCommandEvent& event);
        void OnTextCtrl4Text(wxCommandEvent& event);
        void OnButton2Click(wxCommandEvent& event);
        void OnTextCtrl5Text(wxCommandEvent& event);
        void OnChoice1Select(wxCommandEvent& event);
        void OnChoice2Select(wxCommandEvent& event);
        void OnSlider1CmdScroll(wxScrollEvent& event);
        void OnRadioBox1Select(wxCommandEvent& event);
        void OnSpinCtrl1Change(wxSpinEvent& event);
        void OnChoice3Select(wxCommandEvent& event);
        //*)

        //(*Identifiers(RobotCGenFrame)
        static const long ID_CHOICE1;
        static const long ID_TEXTCTRL2;
        static const long ID_CHOICE2;
        static const long ID_SLIDER1;
        static const long ID_STATICTEXT1;
        static const long ID_CHOICE3;
        static const long ID_SPINCTRL1;
        static const long ID_STATICTEXT2;
        static const long ID_BUTTON1;
        static const long ID_BUTTON2;
        static const long ID_PANEL1;
        //*)

        //(*Declarations(RobotCGenFrame)
        wxSlider* Slider1;
        wxSpinCtrl* SpinCtrl1;
        wxStaticText* StaticText2;
        wxChoice* Choice3;
        wxButton* Button1;
        wxPanel* Panel1;
        wxStaticText* StaticText1;
        wxButton* Button2;
        wxTextCtrl* TextCtrl2;
        wxChoice* Choice1;
        wxChoice* Choice2;
        //*)

        DECLARE_EVENT_TABLE()
};

void setup();
bool process(wxString wxInput, wxString wxMotor, wxString wxSpecial, wxInt16 wxPower, wxString wxMotorType, wxInt16 wxPortNum);

#endif // ROBOTCGENMAIN_H
