#include <iostream>
#include <string>

using namespace std;

class Weather {
protected:
    float temperature;
public:
    Weather(float temperature) {
        this->temperature = temperature;
    }
    virtual bool isDangeours() const = 0;
    virtual void displayWeatherInfo() const = 0;
    virtual ~Weather() {}
};

class SunnyWeather : public Weather {
private:
    float uv;
public:
    SunnyWeather(float temperature, float uv) : Weather(temperature) {
        this->uv = uv;
    }

    bool isDangeours() const override {
        return uv > 8;
    }

    void displayWeatherInfo() const override {
        cout << "The weather is sunny, temperature: " << temperature << "°C, UV index: " << uv;
        if (isDangeours()) {
            cout << ", not recommended to go out";
        }
        cout << endl;
    }
};

class RainyWeather : public Weather {
private:
    float millimeter;
    bool isStorm;
public:
    RainyWeather(float temperature, float millimeter, bool isStorm) : Weather(temperature) {
        this->millimeter = millimeter;
        this->isStorm = isStorm;
    }

    bool isDangeours() const override {
        return isStorm && millimeter > 10;
    }

    void displayWeatherInfo() const override {
        cout << "The weather is rainy, temperature: " << temperature << "°C, amount of rain: " << millimeter << "mm";
        if (isDangeours()) {
            cout << ", not recommended to go out";
        }
        cout << endl;
    }
};

class WindyWeather : public Weather {
private:
    float speed;
    bool isHurricane;
public:
    WindyWeather(float temperature, float speed, bool isHurricane) : Weather(temperature) {
        this->speed = speed;
        this->isHurricane = isHurricane;
    }

    bool isDangeours() const override {
        return isHurricane || speed > 80;
    }

    void displayWeatherInfo() const override {
        cout << "The weather is windy, temperature: " << temperature << "°C, wind speed: " << speed << "km/h";
        if (isDangeours()) {
            cout << ", not recommended to go out";
            if (isHurricane) {
                cout << ", there is a hurricane";
            }
        }
        cout << endl;
    }
};

// Функцијата за филтрирање на ризични временски услови
Weather **getDangerousWeather(Weather **weathers, int n, int &dangerousCount) {
    Weather **tmp = new Weather *[n];
    dangerousCount = 0;
    for (int i = 0; i < n; i++) {
        if (weathers[i]->isDangeours()) {
            tmp[dangerousCount++] = weathers[i];
        }
    }
    return tmp;
}

// Тест во main функцијата
int main() {
    Weather *weathers[5];
    weathers[0] = new SunnyWeather(30, 9.5);
    weathers[1] = new SunnyWeather(25, 4.2);
    weathers[2] = new RainyWeather(20, 12.3, true);
    weathers[3] = new RainyWeather(19, 5.0, false);
    weathers[4] = new WindyWeather(22, 90.0, false);

    cout << "All weather reports:\n";
    for (int i = 0; i < 5; i++) {
        weathers[i]->displayWeatherInfo();
    }

    int dangerousCount = 0;
    Weather **dangerous = getDangerousWeather(weathers, 5, dangerousCount);

    cout << "\nDangerous weather reports:\n";
    for (int i = 0; i < dangerousCount; i++) {
        dangerous[i]->displayWeatherInfo();
    }

    // Clean-up
    for (int i = 0; i < 5; i++) {
        delete weathers[i];
    }
    delete[] dangerous;

    return 0;
}

/*#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class MedicalRecord {
private:
    string patient_id;
    string timestamp;
    int heart_rate;
    int systolic_bp;
    int diastolic_bp;
    double spo2;

    void copy(const MedicalRecord &m) {
        patient_id = m.patient_id;
        timestamp = m.timestamp;
        heart_rate = m.heart_rate;
        systolic_bp = m.systolic_bp;
        diastolic_bp = m.diastolic_bp;
        spo2 = m.spo2;
    }

public:
    MedicalRecord(const string &patient_id = "", const string &timestamp = "", int heart_rate = 0, int systolic_bp = 0, int diastolic_bp = 0, double spo2 = 0.0) {
        this->patient_id = patient_id;
        this->timestamp = timestamp;
        this->heart_rate = heart_rate;
        this->systolic_bp = systolic_bp;
        this->diastolic_bp = diastolic_bp;
        this->spo2 = spo2;
    }

    MedicalRecord(const MedicalRecord &m) {
        copy(m);
    }

    MedicalRecord &operator=(const MedicalRecord &m) {
        if (this != &m) {
            copy(m);
        }
        return *this;
    }

    friend istream &operator>>(istream &in, MedicalRecord &m) {
        in >> m.patient_id >> m.timestamp >> m.heart_rate >> m.systolic_bp >> m.diastolic_bp >> m.spo2;
        return in;
    }

    friend ostream &operator<<(ostream &out, const MedicalRecord &m) {
        out << "Patient with ID: " << m.patient_id << endl;
        out << m.timestamp << " | HR " << m.heart_rate
            << " BP " << m.systolic_bp << "/" << m.diastolic_bp
            << " mmHg SpO2 " << m.spo2 << "%" << endl;
        return out;
    }

    string HealthGroup() const {
        if (heart_rate < 40 || heart_rate > 130 ||
            systolic_bp < 80 || systolic_bp > 180 ||
            diastolic_bp < 50 || diastolic_bp > 110 ||
            spo2 < 90.0) {
            return "Critical";
        }
        if (heart_rate < 50 || heart_rate > 110 ||
            systolic_bp < 90 || systolic_bp > 160 ||
            diastolic_bp < 55 || diastolic_bp > 100 ||
            spo2 < 94.0) {
            return "Monitor";
        }
        return "Healthy";
    }
};

MedicalRecord *FilterByHealthGroup(MedicalRecord *records, int n, string category, int &filteredCount) {
    MedicalRecord *tmp = new MedicalRecord[n];
    filteredCount = 0;
    for (int i = 0; i < n; i++) {
        if (records[i].HealthGroup() == category) {
            tmp[filteredCount++] = records[i];
        }
    }
    return tmp;
}

void writeToFile() {
    ofstream file("text.txt");
    char c;
    while ((c = cin.get()) != '#') {
        file.put(c);
    }
    file.close();
}


int main() {
    writeToFile(); // optional, only if you want to input text interactively with '#' end

    ifstream in("text.txt");
    if (!in) {
        cerr << "Cannot open file\n";
        return 1;
    }

    int testCase, n;
    in >> testCase >> n;

    MedicalRecord *records = new MedicalRecord[n];
    for (int i = 0; i < n; i++) {
        in >> records[i];
    }
    in.close();

    if (testCase == 1) {
        cout << "===== Testing Constructor, Istream Operator & OstreamOperator =====" << endl;
        for (int i = 0; i < n; i++) {
            cout << records[i];
        }
    }

    if (testCase == 2) {
        cout << "===== Testing HealthGroup Function =====" << endl;
        for (int i = 0; i < n; i++) {
            cout << records[i].HealthGroup() << endl;
        }
    }

    if (testCase == 3) {
        cout << "===== Testing FilterByHealthGroup Global Function =====" << endl;
        int count = 0;
        MedicalRecord *filtered = FilterByHealthGroup(records, n, "Healthy", count);
        cout << "Healthy Patients:" << endl;
        for (int i = 0; i < count; i++) {
            cout << filtered[i];
        }
        delete[] filtered;
    }

    if (testCase == 4) {
        cout << "===== Testing FilterByHealthGroup Global Function =====" << endl;
        int count = 0;
        MedicalRecord *filtered = FilterByHealthGroup(records, n, "Critical", count);
        cout << "Critical Patients:" << endl;
        for (int i = 0; i < count; i++) {
            cout << filtered[i];
        }
        delete[] filtered;
    }

    delete[] records;
    return 0;
}
*/