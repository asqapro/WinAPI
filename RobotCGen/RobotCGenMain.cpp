/***************************************************************
 * Name:      RobotCGenMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Adam Whisnant (palidin112@hotmail.com)
 * Created:   2013-07-08
 * Copyright: Adam Whisnant ()
 * License:
 **************************************************************/

#include <vector>
#include <string>

#include "RobotCGenMain.h"
#include "RobotCGenApp.h"
#include <wx/msgdlg.h>
#include <wx/app.h>

//(*InternalHeaders(RobotCGenFrame)
#include <wx/intl.h>
#include <wx/string.h>
//*)

RobotCGenApp app2;

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(RobotCGenFrame)
const long RobotCGenFrame::ID_CHOICE1 = wxNewId();
const long RobotCGenFrame::ID_TEXTCTRL2 = wxNewId();
const long RobotCGenFrame::ID_CHOICE2 = wxNewId();
const long RobotCGenFrame::ID_SLIDER1 = wxNewId();
const long RobotCGenFrame::ID_STATICTEXT1 = wxNewId();
const long RobotCGenFrame::ID_CHOICE3 = wxNewId();
const long RobotCGenFrame::ID_SPINCTRL1 = wxNewId();
const long RobotCGenFrame::ID_STATICTEXT2 = wxNewId();
const long RobotCGenFrame::ID_BUTTON1 = wxNewId();
const long RobotCGenFrame::ID_BUTTON2 = wxNewId();
const long RobotCGenFrame::ID_PANEL1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(RobotCGenFrame,wxFrame)
    //(*EventTable(RobotCGenFrame)
    //*)
END_EVENT_TABLE()

RobotCGenFrame::RobotCGenFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(RobotCGenFrame)
    wxBoxSizer* BoxSizer2;
    wxBoxSizer* BoxSizer1;
    wxBoxSizer* BoxSizer3;

    Create(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    SetClientSize(wxSize(952,135));
    BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
    Panel1 = new wxPanel(this, ID_PANEL1, wxDefaultPosition, wxSize(241,203), wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    BoxSizer2 = new wxBoxSizer(wxVERTICAL);
    Choice1 = new wxChoice(Panel1, ID_CHOICE1, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE1"));
    Choice1->SetSelection( Choice1->Append(_("Controller Input")) );
    Choice1->Append(_("Ch1"));
    Choice1->Append(_("Ch2"));
    Choice1->Append(_("Ch3"));
    Choice1->Append(_("Ch4"));
    Choice1->Append(_("5U"));
    Choice1->Append(_("5D"));
    Choice1->Append(_("6U"));
    Choice1->Append(_("6D"));
    Choice1->Append(_("7U"));
    Choice1->Append(_("7D"));
    Choice1->Append(_("7L"));
    Choice1->Append(_("7R"));
    Choice1->Append(_("8U"));
    Choice1->Append(_("8D"));
    Choice1->Append(_("8L"));
    Choice1->Append(_("8R"));
    BoxSizer2->Add(Choice1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrl2 = new wxTextCtrl(Panel1, ID_TEXTCTRL2, _("Motor Name"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
    BoxSizer2->Add(TextCtrl2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Choice2 = new wxChoice(Panel1, ID_CHOICE2, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE2"));
    Choice2->SetSelection( Choice2->Append(_("Special Cases")) );
    Choice2->Append(_("None"));
    Choice2->Append(_("Constant power"));
    Choice2->Append(_("Motor switch"));
    BoxSizer2->Add(Choice2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Slider1 = new wxSlider(Panel1, ID_SLIDER1, 0, 0, 127, wxDefaultPosition, wxDefaultSize, wxSL_LABELS, wxDefaultValidator, _T("ID_SLIDER1"));
    Slider1->SetSelection(0, 127);
    BoxSizer2->Add(Slider1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText1 = new wxStaticText(Panel1, ID_STATICTEXT1, _("Power (Servo only)"), wxDefaultPosition, wxSize(93,25), 0, _T("ID_STATICTEXT1"));
    BoxSizer2->Add(StaticText1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Choice3 = new wxChoice(Panel1, ID_CHOICE3, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE3"));
    Choice3->SetSelection( Choice3->Append(_("Motor type")) );
    Choice3->Append(_("Servo"));
    Choice3->Append(_("Normal"));
    BoxSizer2->Add(Choice3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SpinCtrl1 = new wxSpinCtrl(Panel1, ID_SPINCTRL1, _T("1"), wxDefaultPosition, wxDefaultSize, 0, 1, 10, 1, _T("ID_SPINCTRL1"));
    SpinCtrl1->SetValue(_T("1"));
    BoxSizer2->Add(SpinCtrl1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText2 = new wxStaticText(Panel1, ID_STATICTEXT2, _("Port Number"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    BoxSizer2->Add(StaticText2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
    Button1 = new wxButton(Panel1, ID_BUTTON1, _("Ok"), wxDefaultPosition, wxSize(116,52), 0, wxDefaultValidator, _T("ID_BUTTON1"));
    BoxSizer3->Add(Button1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Button2 = new wxButton(Panel1, ID_BUTTON2, _("Finish"), wxDefaultPosition, wxSize(116,49), 0, wxDefaultValidator, _T("ID_BUTTON2"));
    BoxSizer3->Add(Button2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer2->Add(BoxSizer3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Panel1->SetSizer(BoxSizer2);
    BoxSizer2->SetSizeHints(Panel1);
    BoxSizer1->Add(Panel1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    SetSizer(BoxSizer1);
    BoxSizer1->SetSizeHints(this);

    Connect(ID_CHOICE1,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&RobotCGenFrame::OnChoice1Select);
    Connect(ID_TEXTCTRL2,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&RobotCGenFrame::OnTextCtrl2Text);
    Connect(ID_CHOICE2,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&RobotCGenFrame::OnChoice2Select);
    Connect(ID_SLIDER1,wxEVT_SCROLL_TOP|wxEVT_SCROLL_BOTTOM|wxEVT_SCROLL_LINEUP|wxEVT_SCROLL_LINEDOWN|wxEVT_SCROLL_PAGEUP|wxEVT_SCROLL_PAGEDOWN|wxEVT_SCROLL_THUMBTRACK|wxEVT_SCROLL_THUMBRELEASE|wxEVT_SCROLL_CHANGED,(wxObjectEventFunction)&RobotCGenFrame::OnSlider1CmdScroll);
    Connect(ID_CHOICE3,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&RobotCGenFrame::OnChoice3Select);
    Connect(ID_SPINCTRL1,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&RobotCGenFrame::OnSpinCtrl1Change);
    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&RobotCGenFrame::OnButton1Click);
    Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&RobotCGenFrame::OnButton2Click);
    //*)
}

RobotCGenFrame::~RobotCGenFrame()
{
    //(*Destroy(RobotCGenFrame)
    //*)
}

void RobotCGenFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void RobotCGenFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}

wxString input; //the controller input
wxString motor; //the motor name
wxString special; //special cases
wxInt32 power; //power for the motor (servo only)
wxString MotorType; //servo or normal
wxInt16 PortNum; //port number (on the brain)

void RobotCGenFrame::OnButton1Click(wxCommandEvent& event) //when the user clicks "Ok"
{
    power = Slider1->GetValue(); //set the power to the slider value
    Close(); //close the GUI
    if(PortNum == 0){ //error catching, just in case
        PortNum = 1;
    }
    if(process(input, motor, special, power, MotorType, PortNum) == false){ //if the process is not finished
        app2.create(); //create the next GUI
    }
}

void RobotCGenFrame::OnTextCtrl2Text(wxCommandEvent& event) //get the motor name
{
    motor = TextCtrl2->GetValue();
}

void RobotCGenFrame::OnButton2Click(wxCommandEvent& event) //when the user clicks "Cancel"
{
    Close(); //close the GUI
    std::string stringItems = ""; //feed in blanks to process
    wxString wxStringItems(stringItems.c_str(), wxConvUTF8);
    wxInt16 wxIntItems = 0;
    process(wxStringItems, wxStringItems, wxStringItems, wxIntItems, wxStringItems, wxIntItems); //this will end process (return false)
}

void RobotCGenFrame::OnChoice1Select(wxCommandEvent& event) //get the controller input to control the motor
{
    input = Choice1->GetString(Choice1->GetCurrentSelection());
}

void RobotCGenFrame::OnChoice2Select(wxCommandEvent& event) //special cases
{
    special = Choice2->GetString(Choice2->GetCurrentSelection());
}

void RobotCGenFrame::OnSlider1CmdScroll(wxScrollEvent& event) //power is set when the user clicks "Ok"
{
}

void RobotCGenFrame::OnSpinCtrl1Change(wxSpinEvent& event) //the port number
{
    PortNum = SpinCtrl1->GetValue();
}

void RobotCGenFrame::OnChoice3Select(wxCommandEvent& event) //the motor type
{
    MotorType = Choice3->GetString(Choice3->GetCurrentSelection());
}
