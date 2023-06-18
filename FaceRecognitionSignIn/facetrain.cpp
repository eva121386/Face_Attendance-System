
#include "facetrain.h"
static void read_csv(const string& filename, vector<Mat>& images, vector<int>& labels);
FaceTrain::FaceTrain()
{
    csvfname="..\\ORL_Faces\\at.txt";

}

FaceTrain::~FaceTrain(){}

void FaceTrain::run(){

    //����at.txt�ļ�
    ofstream outFile(csvfname,ios::out);
    int countfiles=0;
    for(auto& i : filesystem::directory_iterator("..\\ORL_Faces\\")){
        if(i.is_directory()){
            for(auto& j : filesystem::directory_iterator(i)){
                outFile<<j.path().string()<<" "<<countfiles<<endl;
            }
            countfiles++;
        }
    }
    outFile.close();
    cout<<"ORL_FacesĿ¼�����ļ��������"<<endl;
    cout<<"��ȡͼ����"<<endl;
    read_csv(csvfname,images,labels);
    cout<<"��ȡ���"<<endl;
    cout<<"��ʼѵ������ʶ��ģ��"<<endl;
    Mat testSample = images[labels.size() - 1];
    int testLabel = labels[labels.size() - 1];

    images.pop_back();
    labels.pop_back();

    Ptr<face::FaceRecognizer> model = face::EigenFaceRecognizer::create();
    model->train(images, labels);
    model->write("..\\model\\MyFacePCAModel.xml");

//    Ptr<face::FaceRecognizer> model1 = face::FisherFaceRecognizer::create();
//    model1->train(images, labels);
//    model1->write("..\\model\\MyFaceFisherModel.xml");

//    Ptr<face::FaceRecognizer> model2 = face::LBPHFaceRecognizer::create();
//    model2->train(images, labels);
//    model2->write("..\\model\\MyFaceLBPHModel.xml");



    // ����Բ���ͼ�����Ԥ�⣬predictedLabel��Ԥ���ǩ���
    int predictedLabel = model->predict(testSample);
//    int predictedLabel1 = model1->predict(testSample);
//    int predictedLabel2 = model2->predict(testSample);

    // ����һ�ֵ��÷�ʽ�����Ի�ȡ���ͬʱ�õ���ֵ:
    //      int predictedLabel = -1;
    //      double confidence = 0.0;
    //      model->predict(testSample, predictedLabel, confidence);

    string result_message = format("Predicted class = %d / Actual class = %d.", predictedLabel, testLabel);
//    string result_message1 = format("Predicted class = %d / Actual class = %d.", predictedLabel1, testLabel);
//   string result_message2 = format("Predicted class = %d / Actual class = %d.", predictedLabel2, testLabel);
    cout<<"����ʶ��ģ��ѵ����ϣ�ģ��Ԥ������"<<result_message <<endl;
//    cout << result_message1 << endl;
//    cout << result_message2 << endl;
}

//ʹ��CSV�ļ�ȥ��ͼ��ͱ�ǩ����Ҫʹ��stringstream��getline����
static void read_csv(const string& filename, vector<Mat>& images, vector<int>& labels) {
    ifstream file(filename,ios::in);
    if(!file.is_open()){
        cout<<"File does not exist"<<endl;
        return;
    }
    string line,path,classlabel;
    while(getline(file,line)){
        stringstream liness(line);
        getline(liness,path,' ');
        getline(liness,classlabel);

        if (!path.empty() && !classlabel.empty()) {
            images.push_back(imread(path, 0));
            labels.push_back(atoi(classlabel.c_str()));
        }
    }
    file.close();
}
