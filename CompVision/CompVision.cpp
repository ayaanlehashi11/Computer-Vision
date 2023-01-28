#include <wx/wx.h>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
class Frame : public wxFrame
{
public:
    Frame(const wxString& title)
		: wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(650, 570))
	{
	button1->SetForegroundColour(wxColour(*wxGREEN));
	button2->SetForegroundColour(wxColour(*wxLIGHT_GREY));
	button2->Bind(wxEVT_BUTTON,[&](wxCommandEvent& event)
{
  text->SetValue("");
  static const int max = 10;
   wxProgressDialog dialog(wxT("Progress Dialog example"),wxT("An informative message"),max,this ,wxPD_CAN_ABORT|wxPD_APP_MODAL|wxPD_ELAPSED_TIME|wxPD_ESTIMATED_TIME|wxPD_REMAINING_TIME);
   dialog.SetBackgroundColour(wxColour(*wxWHITE));
   bool cont = true;
   for(int i = 0;i<=max;i++)
   {
      wxSleep(1);
      if(i == max)
         cont = dialog.Update(i , wxT("Completed"));
      else if(i == max /2)
         cont = dialog.Update(i , wxT("Already There"));
      else
         cont = dialog.Update(i);
      if(!cont){
         if(wxMessageBox(wxT("Do you realy want to cancel?"),
                        wxT("progress dialog question"),
                        wxYES_NO | wxICON_QUESTION) == wxYES)
                        break;
         dialog.Resume();
      }  
          }
          if(!cont)
             wxLogStatus(wxT("Progress dialog aborted"));
          else
             wxLogStatus(wxT("Countdown from %d finished") , max);
});
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
	static void ShowProgress();
       
public:  
    wxPanel* panel = new wxPanel(this);
    wxTextCtrl* text = new wxTextCtrl(panel , wxID_ANY,wxEmptyString , wxDefaultPosition,wxSize(240 , 100),wxTE_MULTILINE);
    wxButton* button1 = new wxButton(panel , wxID_ANY, "button1",{170 , 140});
    wxButton* button2 = new wxButton(panel , wxID_ANY, "button2",{230 , 170});
    wxCheckBox* check = new wxCheckBox(panel , wxID_ANY , wxT("&check me"),wxDefaultPosition , wxDefaultSize);
    check->SetValue(true);
};
void Frame :: ShowProgress()
{
   
}
class MyApp : public wxApp
{
public:
	bool OnInit()
	{
		Frame *frame = new Frame(wxT("CompVision"));
		frame->Show(true);
		frame->SetBackgroundColour(wxColour(169 , 169 , 169));
		return true;
	}
};

wxIMPLEMENT_APP(MyApp);






