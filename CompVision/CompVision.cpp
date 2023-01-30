#include <wx/wx.h>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <wx/slider.h>
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

	slider->SetForegroundColour(wxColour(*wxGREEN));
	text->SetForegroundColour(wxColour(*wxGREEN));
	text->SetDefaultStyle(wxTextAttr(*wxGREEN));
	slider->Bind(wxEVT_SLIDER,[&](wxCommandEvent& event)
	{
	    cout << "the Current Slider value is: " << slider->GetValue() << endl;
	});
	/**this button helps you to exit and finish the whole program
	*/
	halt->Bind(wxEVT_BUTTON,[&](wxCommandEvent& event){
	    exit(1);
	});
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
	            cout << "Ayaanle is here baby..." << endl;
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
	void HandDetection(Mat& img , CascadeClassifier* cascade , double scale);
       
public:  
    wxPanel* panel = new wxPanel(this);
    wxTextCtrl* text = new wxTextCtrl(panel , wxID_ANY,wxEmptyString , {100 , 170},wxSize(440 , 100),wxTE_MULTILINE);
    wxButton* button1 = new wxButton(panel , wxID_ANY, "grey",{316 , 10});
    wxButton* button2 = new wxButton(panel , wxID_ANY, "detect",{130 , 10});
    wxButton* button3 = new wxButton(panel , wxID_ANY, "click", {40 , 10});
    wxButton* halt = new wxButton(panel , wxID_ANY,"halt",{224 , 10});
    wxSlider* slider = new wxSlider(panel , wxID_ANY , 16, 0 , 100,{400 , 100},wxSize(200 , -1),wxSL_HORIZONTAL|wxSL_AUTOTICKS|wxSL_LABELS);
        wxTextCtrl* text1 = new wxTextCtrl(panel , wxID_ANY,wxEmptyString , {100 , 400},wxSize(440 , 100),wxTE_MULTILINE);
    
};



/**
Mat stream;
	            VideoCapture cap(0);
	            namedWindow("Face Detection");
	            string classifier_path = "/home/ayaanle/opencv-build/opencv/data/haarcascade/haarcascade_frontalcatface.xml";
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
	                  rectangle(stream , Point(x , y),Point(w , h),Scalar(255 , 0 , 255),2 , 8 , 0);
	               }
	               imshow("Face Detection" , stream);
	               if(waitKey(10) == 27)
	                  break;
	            }
*/



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






