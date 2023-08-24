#include <iostream>
#include <string>
#include <unordered_set>

using namespace std;

class NotificationAlertObserver {
    public:
        virtual void update(int currentStock) = 0;
};

class StockObservable {
    public:
        virtual void add(NotificationAlertObserver * obj) = 0;
        virtual void remove(NotificationAlertObserver * obj) = 0;
        virtual void notify(int currentStock) = 0;
        virtual void updateData(int currentStock) = 0;
        virtual int getData() = 0;
};

class StockObservableImpl : public StockObservable {
    unordered_set<NotificationAlertObserver*, bool> observerSet;
    int stock = 0;
    
    public:
        void add(NotificationAlertObserver* obj) {
            observerSet.insert(obj);
        }
        void remove(NotificationAlertObserver* obj) {
            observerSet.erase(obj);
        }
        void notify(int currentStock) {
            for (auto &&i : observerSet) {
                i->update(currentStock);
           }  
        }

        void updateData(int currentStock) {
            this->stock = currentStock;
            this->notify(currentStock);
        }

        int getData() {
            return stock;
        }
};


class EmailAlertObserver: public NotificationAlertObserver {
    string emailId;
    StockObservable* observable;
    public: 
        EmailAlertObserver(string emailId, StockObservable* observable) {
            this->emailId = emailId;
            this->observable = observable;
        }

        void sendEmail(int currentStock) {
            cout<<"sending mail with current stock"<<" "<<currentStock<<" "<<"to"<<this->emailId<<"\n";
        }

        void update(int currentStock) {
            this->sendEmail(currentStock);
        }
};

class MessageAlertObserver: public NotificationAlertObserver {
    string phoneNo;
    StockObservable* observable;
    public: 
        MessageAlertObserver(string phoneNo, StockObservable* observable) {
            this->phoneNo = phoneNo;
            this->observable = observable;
        }

        void sendMessage(int currentStock) {
            cout<<"sending message with current stock"<<" "<<currentStock<<" "<<"to"<<this->phoneNo<<"\n";
        }

        void update(int currentStock) {
            this->sendMessage(currentStock);
        }
};

int main() {
    StockObservable* iPhoneObservable = new StockObservableImpl();
    NotificationAlertObserver* emailObserver1 = new EmailAlertObserver("abc@gmail.com", iPhoneObservable);
    NotificationAlertObserver* emailObserver2 = new EmailAlertObserver("abcd@gmail.com", iPhoneObservable);
    NotificationAlertObserver* phoneObserver1 = new EmailAlertObserver("123456", iPhoneObservable);

    iPhoneObservable->add(emailObserver1);
    iPhoneObservable->add(emailObserver2);
    iPhoneObservable->add(phoneObserver1);

    iPhoneObservable->updateData(2);


    return 0;
}
