
#include <iostream>
#include <mutex>
#include <wx/wx.h>
#include <wx/dialog.h>
#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <opencv2/ml.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/video.hpp>
#include <opencv2/videoio.hpp>
#include <thread>
#include <filesystem>
#include <fstream>
using namespace std;
using namespace cv;


Frame :: Frame(const wxString& title):wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(650, 570)){
     button1->SetForegroundColour(wxColour(*wxGREEN));
	button2->SetForegroundColour(wxColour(*wxLIGHT_GREY));
	button2->Bind(wxEVT_BUTTON,[&](wxCommandEvent& event)
{
  text->SetValue("");
  
	        button1->Bind(wxEVT_BUTTON, [&](wxCommandEvent& event){
	             std::cout << "Recording a Video..." << std::endl;
	Mat image;
        VideoCapture cap(0);
        if (!cap.isOpened()){
           cout << "No video stream available at the moment " << endl;
           system("pause");

   }
        while(true)
           {
           cap >> image;
           if(image.empty())
              break;

           imshow("CompVision",image);
           char c = (char)waitKey(25);
           if(c == 27){
              break;
              }
   }      cout << "recording a video... " << endl;
          cap.release();
          cout << "stopping the streamer... " << endl;
	        });
		Centre();
	}

bool App :: OnInit(){
     Frame* frame = new Frame(wxT("CompVision"));
     frame->Show(true);
     frame->SetBackgroundColour(wxColour(169 , 169 , 169));
     return true;
}
class Frame : public wxFrame{
public:
      Frame(const wxString& title):wxFrame(NULL , wxID_ANY , title , wxDefaultPosition , wxSize(200 , 20)){
      inline void show_dialog();
      void vision();
public:
    wxPanel* panel = new wxPanel(this);
    wxTextCtrl* text = new wxTextCtrl(panel , wxID_ANY,wxEmptyString , wxDefaultPosition,wxSize(240 , 100),wxTE_MULTILINE);
    wxButton* button1 = new wxButton(panel , wxID_ANY, "button1",{170 , 140});
    wxButton* button2 = new wxButton(panel , wxID_ANY, "button2",{230 , 170});
};
class App:public wxApp{
   bool OnInit();
};
wxIMPLEMENT_APP(App);
