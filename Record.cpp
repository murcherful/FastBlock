#include "Record.h"

bool scoreInfoCmp(scoreInfo a, scoreInfo b){
    return a.score > b.score;
}


Record::Record(int w, int h, std::string tFileName){
    fileName = tFileName;
    outW = w;
    outH = h;
}

Record::~Record(){

}

void Record::record(int score){
    readFile();
    if(infos.size() < 10 || score > infos[9].score){
        //std::cout << "less than 10" << std::endl;
        std::string name = getName(score);
        scoreInfo temp;
        temp.score = score;
        temp.name = name;
        infos.push_back(temp);
        sort(infos.begin(), infos.end(), scoreInfoCmp);
        writeFile(); 
    }
    infos.clear();
}

void Record::readFile(){
    std::fstream file;
    file.open(fileName.c_str());
    scoreInfo temp;
    while(file >> temp.name >> temp.score){
        infos.push_back(temp);
    }
    file.close();
}

void Record::writeFile(){
    std::ofstream file;
    file.open(fileName.c_str(), std::fstream::out);
    for(int i = 0; i < std::min(10, (int)infos.size()); ++i){
        file << infos[i].name << " " << infos[i].score << std::endl;
    }
    file.close();
}

std::string Record::getName(int score){
    int shiftX = (outW - RECORDW)/2;
    int shiftY = (outH - RECORDH)/2;
    stringstream ssScore;
    ssScore << "SCORE: " << score;
    drawRect(shiftX, shiftY, RECORDW, RECORDH, BULE);
    drawWholeRect(shiftX+1, shiftY+1, RECORDW-2, RECORDH-2, WHITE);
    drawText(shiftX+2, shiftY+2, ssScore.str(), WHITE, BLACK);
    drawText(shiftX+2, shiftY+4, "NAME:                           ", WHITE, BLACK);
    close_keyboard();
    cout << "\033[?25h\n";
    printf("\033[%d;%dH\033[3%dm\033[4%dm", shiftY+4+1, (shiftX+2)*2+6+1, WHITE, BLACK);
    std::string name;
    cin>>name;
    init_keyboard();
    cout << "\033[?25l\n"; 
    return name;
}

void Record::show(){
    int shiftX = (outW - SHOWW)/2;
    int shiftY = (outH - SHOWH)/2;
    drawRect(shiftX, shiftY, SHOWW, SHOWH, BULE);
    drawWholeRect(shiftX+1, shiftY+1, SHOWW-2, SHOWH-2, WHITE);
    readFile(); 
    drawText(shiftX+2, shiftY+2, "SCORE BOARD", WHITE, YELLOW);
    for(int i = 0; i < std::min(10, (int)infos.size()); ++i){
        std::stringstream ssText;
        ssText << i+1 << ": " << infos[i].name << " " << infos[i].score;
        if(i == 0){
            drawText(shiftX+2, shiftY+2*(i+2), ssText.str(), WHITE, RED);
        }
        else if(i == 1){
            drawText(shiftX+2, shiftY+2*(i+2), ssText.str(), WHITE, BULE);
        }
        else if(i == 2){
            drawText(shiftX+2, shiftY+2*(i+2), ssText.str(), WHITE, GREEN);
        }
        else{
            drawText(shiftX+2, shiftY+2*(i+2), ssText.str(), WHITE, BLACK);
        }
    }
    infos.clear();
}
