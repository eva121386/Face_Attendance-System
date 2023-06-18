
#include "faceget.h"

FaceGet::FaceGet()
{
    if (!face_cascade_.load("..\\haarcascades\\haarcascade_frontalface_alt.xml"))
    {
        cerr << "ERROR: Could not load face classifier." << endl;
        return;
    }
}

FaceGet::~FaceGet(){}

Mat FaceGet::getFrame(Mat frame){
    if (frame.empty())
    {
        cerr << "ERROR: Blank frame." << endl;
    }

    // ��ͼ��ת��Ϊ�Ҷ�ͼ
    Mat gray;
    cvtColor(frame, gray, COLOR_BGR2GRAY);
    equalizeHist(gray,gray);
    // �������
    vector<Rect> faces;
    face_cascade_.detectMultiScale(gray, faces);

    // ��ͼ���л����������β���ȡ����ͼ��
    for (size_t i = 0; i < faces.size(); i++)
    {
        rectangle(frame, faces[i], Scalar(0, 255, 0), 2);
    }

    return frame;
}


void FaceGet::savePic(string name,int face_count,Mat frame){
    string dir_name_ = "..\\ORL_Faces\\faces_"+name;
    if(_access(dir_name_.c_str(),0)!=0){
        mkdir(dir_name_.c_str());
    }

    Mat gray;
    cvtColor(frame, gray, COLOR_BGR2GRAY);
    equalizeHist(gray,gray);
    // �������
    vector<Rect> faces;
    face_cascade_.detectMultiScale(gray, faces);


    //rectangle(frame, faces[i], Scalar(0, 255, 0), 2);
    // ��ȡ����ͼ��
    Mat face = frame(faces[0]);
    resize(face,face,Size(92,112));

    string filename = dir_name_ +"\\" + to_string(face_count) + ".jpg";

    // ����ͼ���ļ�
    imwrite(filename, face);

}
