#include <wx/wx.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <vector>
#include <string>
using namespace std;
using namespace cv;


class Frame : public wxFrame
{
public:
    Frame(const wxString& title)
		: wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(650, 570))
	{
	text->SetForegroundColour(wxColour(*wxGREEN));
	text->SetDefaultStyle(wxTextAttr(*wxGREEN));
	button2->Bind(wxEVT_BUTTON,[&](wxCommandEvent& event){
	text->SetValue("Detecting the face of the user...");
	cout << "Detecting the face of the user..." << endl;
	    Mat stream;
	            
	            VideoCapture cap(0);
	            namedWindow("Face Detection");
	            string classifier_path = "/usr/local/share/opencv4/haarcascades/haarcascade_frontalcatface.xml";
	            CascadeClassifier faceDetector;
	            faceDetector.load(classifier_path);

	            vector<Rect>faces;
	            while(true){
	               faceDetector.detectMultiScale(stream , faces , 1.1 , 1 , 0 |CASCADE_SCALE_IMAGE,Size(30 , 30));
	               cap.read(stream);
	               for(int i = 0; i < faces.size();++i){
	                  Mat faceROI = stream(faces[i]);
	                  int x = faces[i].x;
	                  int y = faces[i].y;
	                  int h = y + faces[i].height;
	                  int w = x + faces[i].width;
	                  rectangle(stream , Point(x , y),Point(w , h),Scalar(0 , 255 , 0),2 , 8 , 0);
	               }
	               imshow("Face Detection" , stream);
	               if(waitKey(10) == 27)
	                  break;
	              }
	              text->SetValue("Detecting the face of the user...");
	            
	});
         //basic video recorder
	        button1->Bind(wxEVT_BUTTON, [&](wxCommandEvent& event){
	            cout << "Video recording without Detection..." << endl;
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

public:
    ~Frame():~wxFrame()
    {
       delete panel;
       delete button1;
       delete button2;
       delete text;
       delete text1;
    }
      
public:  
    wxPanel* panel = new wxPanel(this);
    wxTextCtrl* text = new wxTextCtrl(panel , wxID_ANY,wxEmptyString , {100 , 170},wxSize(440 , 100),wxTE_MULTILINE);
    wxButton* button1 = new wxButton(panel , wxID_ANY, "detect",{130 , 10});
    wxButton* button2 = new wxButton(panel , wxID_ANY, "record", {40 , 10});
        wxTextCtrl* text1 = new wxTextCtrl(panel , wxID_ANY,wxEmptyString , {100 , 400},wxSize(440 , 100),wxTE_MULTILINE);
    
};



class MyApp : public wxApp
{
public:
	bool OnInit()
	{
		Frame *frame = new Frame(wxT("CompVision"));
		frame->Show(true);
		//frame->SetBackgroundColour(wxColour(128 , 128 , 128));
		return true;
	}
};

wxIMPLEMENT_APP(MyApp);






