#include<iostream>;
using namespace std;

//ģ����
template<class T>
class Callback {
public:
	void onSuccess(T result) {
		cout << result << endl;
	}

	void onError(string msg) {
		cout << msg << endl;
	}
};

//���಻��ģ����

class IntCallback :public Callback<int> {
public:
	void onSuccess(int result) {
		Callback::onSuccess(result);
		cout << "����IntCallback" << endl;
	}
};

//����Ҳ��ģ����
template<class T>
class HttpCallback :public Callback<T>{
public:
	void onSuccess(T result) {
		Callback<T>::onSuccess(result);
		cout << "����HttpCallback" << endl;
	}

};


void main(void) {

	Callback<int>* callback = new Callback<int>();

	callback->onSuccess(35);


	IntCallback* intCallback = new IntCallback();
	intCallback->onSuccess(36);
	

	HttpCallback<string>* httpCallback = new HttpCallback<string>();
	httpCallback->onSuccess("hello world");


	getchar();
}