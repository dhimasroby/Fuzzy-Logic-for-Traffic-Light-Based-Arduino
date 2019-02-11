#include <Fuzzy.h>
#include <FuzzyComposition.h>
#include <FuzzyInput.h>
#include <FuzzyIO.h>
#include <FuzzyOutput.h>
#include <FuzzyRule.h>
#include <FuzzyRuleAntecedent.h>
#include <FuzzyRuleConsequent.h>
#include <FuzzySet.h>

//Pengganti Sensor Sementara, untuk memudahkan penggantian angka
/*int rule1(30);
int rule2(20);
int rule3(10);
int rule4(0);
*/
long rule1;
long rule2;
long rule3;
long rule4;

Fuzzy* fuzzy = new Fuzzy();
FuzzySet* penSedikit = new FuzzySet (0,3,9,12);
FuzzySet* penNormal = new FuzzySet (15,18,21,24);
FuzzySet* penRamai = new FuzzySet (21,27,30,30);

FuzzySet* hatiHati  = new FuzzySet (0,0,0,0);
FuzzySet* lama = new FuzzySet (0,5,5,15);
FuzzySet* normal = new FuzzySet (10,15,15,30);
FuzzySet* cepat = new FuzzySet (15,30,40,40);

FuzzySet* kendSedikit = new FuzzySet (0,3,6,9);
FuzzySet* kendNormal = new FuzzySet (8,10,12,14);
FuzzySet* kendRamai = new FuzzySet (15,16,18,20);

int kendHij1 = 13;
int kendKun1 = 12;
int kendMer1 = 11;
int penHij1 = 10;
int penKun1 = 9;
int penMer1 = 8;
int kendHij2 = 7;
int kendKun2 = 6;
int kendMer2 = 5;
int penHij2 = 4;
int penKun2 = 3;
int penMer2 = 2;

void setup() {
  Serial.begin(9600);
  Serial.println("========================");
  Serial.println("Fuzzy Logic untuk Lampu Penyebrang Jalan");
  Serial.println("========================");
  pinMode (kendHij1, OUTPUT);
  pinMode (kendHij2, OUTPUT);
  pinMode (kendMer1, OUTPUT);
  pinMode (kendMer2, OUTPUT);
  pinMode (kendKun1, OUTPUT);
  pinMode (kendKun2, OUTPUT);
  pinMode (penHij1, OUTPUT);
  pinMode (penHij2, OUTPUT);
  pinMode (penKun1, OUTPUT);
  pinMode (penKun2, OUTPUT);
  pinMode (penMer1, OUTPUT);
  pinMode (penMer2, OUTPUT);
  delay(3000);
  Serial.print("Inisialisasi.");
  delay(1000);
  Serial.print(".");
  delay(1000);
  Serial.println(".");
  delay(1000);
  
  // FuzzyInput
  FuzzyInput* jumPenyabrang = new FuzzyInput(1);
  jumPenyabrang->addFuzzySet(penSedikit);
  jumPenyabrang->addFuzzySet(penNormal);
  jumPenyabrang->addFuzzySet(penRamai);

  fuzzy->addFuzzyInput(jumPenyabrang);

  // FuzzyInput
  FuzzyInput* jumKendaraan = new FuzzyInput(2);
  jumKendaraan->addFuzzySet(kendSedikit);
  jumKendaraan->addFuzzySet(kendNormal);
  jumKendaraan->addFuzzySet(kendRamai);

  fuzzy->addFuzzyInput(jumKendaraan);

  // FuzzyOutput
  FuzzyOutput* lamaLampu = new FuzzyOutput(1);
  lamaLampu->addFuzzySet(hatiHati);
  lamaLampu->addFuzzySet(lama);
  lamaLampu->addFuzzySet(normal);
  lamaLampu->addFuzzySet(cepat);

  fuzzy->addFuzzyOutput(lamaLampu);

  //Peraturan Fuzzy
  FuzzyRuleAntecedent* IFpenRamaiDanKenRamai = new FuzzyRuleAntecedent();
  IFpenRamaiDanKenRamai->joinWithAND(penRamai,kendRamai);
  FuzzyRuleConsequent* makaLampuNormal = new FuzzyRuleConsequent();
  makaLampuNormal->addOutput(normal);

  FuzzyRule* fuzzyRule1 = new FuzzyRule(1, IFpenRamaiDanKenRamai, makaLampuNormal);
  fuzzy->addFuzzyRule(fuzzyRule1); 

  //Peraturan Fuzzy
  FuzzyRuleAntecedent* IFpenRamaiDanKenSepi = new FuzzyRuleAntecedent();
  IFpenRamaiDanKenSepi->joinWithAND(penRamai,kendSedikit);
  FuzzyRuleConsequent* makaLampuLama = new FuzzyRuleConsequent();
  makaLampuLama->addOutput(lama);

  FuzzyRule* fuzzyRule2 = new FuzzyRule(2, IFpenRamaiDanKenSepi, makaLampuLama);
  fuzzy->addFuzzyRule(fuzzyRule2); 

  //Peraturan Fuzzy
  FuzzyRuleAntecedent* IFpenSepiDanKenRamai = new FuzzyRuleAntecedent();
  IFpenSepiDanKenRamai->joinWithAND(penSedikit,kendRamai);
  FuzzyRuleConsequent* makaLampuCepat = new FuzzyRuleConsequent();
  makaLampuCepat->addOutput(cepat);

  FuzzyRule* fuzzyRule3 = new FuzzyRule(3, IFpenSepiDanKenRamai, makaLampuCepat);
  fuzzy->addFuzzyRule(fuzzyRule3); 

  //Peraturan Fuzzy
  FuzzyRuleAntecedent* IFpenSepiDanKenSepi = new FuzzyRuleAntecedent();
  IFpenSepiDanKenSepi->joinWithAND(penSedikit,kendSedikit);
  FuzzyRuleConsequent* makaLampuKuning = new FuzzyRuleConsequent();
  makaLampuKuning->addOutput(hatiHati);

  FuzzyRule* fuzzyRule4 = new FuzzyRule(4, IFpenSepiDanKenSepi, makaLampuKuning);
  fuzzy->addFuzzyRule(fuzzyRule4); 
  randomSeed(analogRead(A0));
}
void Reset() {
    digitalWrite(kendHij1, LOW);
    digitalWrite(kendHij2, LOW);
    digitalWrite(penHij1, LOW);
    digitalWrite(penHij2, LOW);
    digitalWrite(penMer1, LOW);
    digitalWrite(penMer2, LOW);
    digitalWrite(kendMer1, LOW);
    digitalWrite(kendMer2, LOW);
    digitalWrite(kendKun1, LOW);
    digitalWrite(kendKun2, LOW);
    digitalWrite(penKun1, LOW);
    digitalWrite(penKun2, LOW);
}

void HatiHati() {
    digitalWrite(kendKun1, HIGH);
    digitalWrite(kendKun2, HIGH);
    digitalWrite(penKun1, HIGH);
    digitalWrite(penKun2, HIGH);
    delay(1000);
    digitalWrite(kendKun1, LOW);
    digitalWrite(kendKun2, LOW);
    digitalWrite(penKun1, LOW);
    digitalWrite(penKun2, LOW);
    delay(1000);
    digitalWrite(kendKun1, HIGH);
    digitalWrite(kendKun2, HIGH);
    digitalWrite(penKun1, HIGH);
    digitalWrite(penKun2, HIGH);
    delay(1000);
    digitalWrite(kendKun1, LOW);
    digitalWrite(kendKun2, LOW);
    digitalWrite(penKun1, LOW);
    digitalWrite(penKun2, LOW);
    delay(1000);
    digitalWrite(kendKun1, HIGH);
    digitalWrite(kendKun2, HIGH);
    digitalWrite(penKun1, HIGH);
    digitalWrite(penKun2, HIGH);
    delay(1000);
    digitalWrite(kendKun1, LOW);
    digitalWrite(kendKun2, LOW);
    digitalWrite(penKun1, LOW);
    digitalWrite(penKun2, LOW);
    delay(1000);
    digitalWrite(kendKun1, HIGH);
    digitalWrite(kendKun2, HIGH);
    digitalWrite(penKun1, HIGH);
    digitalWrite(penKun2, HIGH);
    delay(1000);
    digitalWrite(kendKun1, LOW);
    digitalWrite(kendKun2, LOW);
    digitalWrite(penKun1, LOW);
    digitalWrite(penKun2, LOW);
    delay(1000);
 }

void loop() { 
  Serial.println("Virtual Sensor"); 
  rule1 = random(1,20);
  rule2 = random(1,30);
  rule3 = random(1,20);
  rule4 = random(1,30);
  fuzzy->setInput(1, rule1);
  fuzzy->setInput(2, rule2);
  fuzzy->setInput(3, rule3);
  fuzzy->setInput(4, rule4);  
  Serial.print("Jumlah Kendaraan : ");
  Serial.println(rule2 + rule4);
  Serial.print("Jumlah Penyebrang : ");
  Serial.println(rule1 + rule3);
  
  fuzzy->fuzzify();
  /*Serial.print("Penyebrang : ");
  Serial.print(penSedikit->getPertinence());
  Serial.print(", ");
  Serial.print(penNormal->getPertinence());
  Serial.print(", ");
  Serial.println(penRamai->getPertinence());
  Serial.print("Kendaraan : ");
  Serial.print(kendSedikit->getPertinence());
  Serial.print(", ");
  Serial.print(kendNormal->getPertinence());
  Serial.print(", ");
  Serial.println(kendRamai->getPertinence());
*/
  float output1 = fuzzy->defuzzify(1);
  
  if (output1 == 0) {
    Serial.println("Lampu dalam mode Hati-hati");
    Reset();
    HatiHati();  
    }
    else if (output1 >= 30 ) {
      Serial.println("Lampu dalam mode Lama");
    Reset();
    ModeOn(output1);
    }
    else if (output1 >= 20 ) {
      Serial.println("Lampu dalam mode Normal");
    Reset();  
    ModeOn(output1);
    }
    else {
    Serial.println("Lampu dalam mode Cepat");
    Reset();
    ModeOn(output1);
    }
}

void ModeOn(float a) {
      digitalWrite(kendHij1, HIGH);
      digitalWrite(kendHij2, HIGH);
      digitalWrite(penMer1, HIGH);
      digitalWrite(penMer2, HIGH);
      Serial.print("Lampu Hijau untuk kendaraan dalam ");
      Serial.print(a);
      Serial.println(" detik");
      delay(a*1000);
      digitalWrite(kendHij1, LOW);
      digitalWrite(kendHij2, LOW);
      digitalWrite(kendKun1, HIGH);
      digitalWrite(kendKun2, HIGH);
      Serial.println("Jeda Lampu Kuning 2 detik ");
      delay(2000);
      digitalWrite(kendKun1, LOW);
      digitalWrite(kendKun2, LOW);
      digitalWrite(penMer1, LOW);
      digitalWrite(penMer2, LOW);
      digitalWrite(kendMer1, HIGH);
      digitalWrite(kendMer2, HIGH);
      digitalWrite(penHij1, HIGH);
      digitalWrite(penHij2, HIGH);
      Serial.print("Lampu Hijau untuk penyabrang dalam ");
      Serial.print(a);
      Serial.println(" detik");
      delay(a*1000);
      digitalWrite(penHij1, LOW);
      digitalWrite(penHij2, LOW);
      digitalWrite(penKun1, HIGH);
      digitalWrite(penKun2, HIGH);
      Serial.println("Jeda Lampu Kuning 2 detik ");
      delay(2000);
      digitalWrite(penKun1, LOW);
      digitalWrite(penKun2, LOW);
      digitalWrite(kendMer1, LOW);
      digitalWrite(kendMer2, LOW);
}
