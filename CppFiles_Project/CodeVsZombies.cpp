#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <climits>
#include <cstdlib>
using namespace std;

/**
 * Save humans, destroy zombies!
 **/
typedef struct HStruct
{
    int id;
    int x, y;
}HStruct;

typedef struct ZStruct
{
    int id;
    int x, y;
    int nextX, nextY;
}ZStruct;

vector<HStruct> hVector;
vector<ZStruct> zVector;

int findDistance(int x1, int y1, int x2, int y2)
{
    int yDis, xDis;
    int ans = 0;
    yDis = abs(y2-y1);
    xDis = abs(x2-x1);
    ans = xDis*xDis + yDis*yDis;
    ans = sqrt(ans);
    return ans;
}

int moveTowardHuman(int x, int y)
{
    int zombieToHuman = INT_MAX;
    
    int sizeZ = zVector.size();
    int sizeH = hVector.size();
    
    int id = sizeH;
    
    int ashDistanceToHuman;
    int numberOfStepAsh;
    int numberOfStepZombie = INT_MAX;
    int tempStep;
    
    for(int i = 0; i < sizeZ; ++i)
    {
        for(int j = 0; j < sizeH; ++j)
        {
            ashDistanceToHuman = findDistance(x, y, hVector[j].x, hVector[j].y);
            numberOfStepAsh = ashDistanceToHuman / 1500;
            int distance = findDistance(zVector[i].nextX, zVector[i].nextY, hVector[j].x, hVector[j].y);
            
            if(distance < zombieToHuman)
            {
                tempStep = distance / 400;
                if(tempStep < numberOfStepAsh)
                {
                    //Don't chnage as we can't save him
                    ;
                }
                else
                {
                    zombieToHuman = distance;
                    numberOfStepZombie = zombieToHuman / 400;
                    id = j;
                }
            }
        }
    }
    
    {
        cerr << "id = " << id << endl;
        cerr << "ZombieStep = " << numberOfStepZombie << ", ashStep = " << numberOfStepAsh << endl;
        if(numberOfStepZombie < numberOfStepAsh)
        {
           id = sizeH;
        }
    }
    return id;
}

int moveTowardZombie()
{
    int size = zVector.size();
    vector<int> zombieCircle(size, 0);
    
    int max = -1;
    int id = size;
    for(int i = 0; i < size; ++i)
    {
        int x = zVector[i].x;
        int y = zVector[i].y;
        
        int minX, maxX, minY, maxY;
        
        minX = x-2000 < 0 ? 0 : x-2000;
        maxX = x+2000 > 16000 ? 16000 : x+2000;

        minY = y-2000 < 0 ? 0 : y-2000;
        maxY = y+2000 > 9000 ? 9000 : y+2000;
        
        
        for(int j = 0; j < size; ++j)
        {
            if(i == j)
                continue;
            
            if((zVector[j].nextX >= minX || zVector[j].nextX <= maxX)
                && (zVector[j].nextY >= minY || zVector[j].nextY <= maxY))
            {
                zombieCircle[i]++;
            }
        }
        if(max < zombieCircle[i])
        {
            max = zombieCircle[i];
            id = i;
        }
    }
    
    return id;
}

int NumberOfHumanWeCanSave(int ashX, int ashY, int &specialId)
{
    int weCanSave = 0;
    int zombieToHuman = INT_MAX;
    
    int sizeZ = zVector.size();
    int sizeH = hVector.size();
    
    vector<int> stepsFromZombie(sizeH, INT_MAX);
    int x, y;
    
    int numberOfSteps;
    
    for(int i = 0; i < sizeH; i++)
    {
        x = hVector[i].x;
        y = hVector[i].y;
        
        for(int j = 0; j < sizeZ; j++)
        {
            numberOfSteps = findDistance(x, y, zVector[j].x, zVector[j].y)/400;
            if(stepsFromZombie[i] > numberOfSteps)
            {
                stepsFromZombie[i] = numberOfSteps;
            }
        }
    }
    
    vector<int> stepsFromAsh(sizeH, INT_MAX);
    for(int i = 0; i < sizeH; i++)
    {
        x = hVector[i].x;
        y = hVector[i].y;
        stepsFromAsh[i] = findDistance(x, y, ashX, ashY)/1500;
    }
    
    for(int i = 0; i < sizeH; i++)
    {
        if(stepsFromAsh[i] <= stepsFromZombie[i])
        {
            weCanSave++;
            specialId = i;
        }
    }
    
    cerr << "WeCanSave = " << weCanSave << ", id = " << specialId << endl;
    return weCanSave;
}
 
int main()
{
    int specialId = -1;
    // game loop
    while (1) {
        int x;
        int y;
        cin >> x >> y; cin.ignore();
        int humanCount;
        hVector.clear();
        zVector.clear();
        cin >> humanCount; cin.ignore();
        for (int i = 0; i < humanCount; i++) {
            int humanId;
            int humanX;
            int humanY;
            cin >> humanId >> humanX >> humanY; cin.ignore();
            HStruct humanS;
            humanS.id = humanId;
            humanS.x = humanX;
            humanS.y = humanY;
            hVector.push_back(humanS);
        }
        int zombieCount;
        cin >> zombieCount; cin.ignore();
        for (int i = 0; i < zombieCount; i++) {
            int zombieId;
            int zombieX;
            int zombieY;
            int zombieXNext;
            int zombieYNext;
            cin >> zombieId >> zombieX >> zombieY >> zombieXNext >> zombieYNext; cin.ignore();
            
            ZStruct zombieS;
            zombieS.id = zombieId;
            zombieS.x = zombieX;
            zombieS.y = zombieY;
            zombieS.nextX = zombieXNext;
            zombieS.nextY = zombieYNext;
            zVector.push_back(zombieS);
        }

        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;
        int moveX, moveY;
        int humanWeCanSave;
        int tempId;
        
        
        int id = moveTowardHuman(x, y);

        static bool once = false;
        
        if(NumberOfHumanWeCanSave(x, y, tempId) <= 1)
        {
           if(!once)
            {
                once = true;
                if(tempId >= humanCount)
                {
                    specialId = 0;
                }
                else
                {
                    specialId = tempId;
                }
            }
        }

        /*if(humanCount == 1 && id == humanCount)
        {
            moveX = hVector[0].x;
            moveY = hVector[0].y;
        }
        else */
        if(once)
        {
            //Find which one we can save
            cerr << "WeCanSave : id = " << specialId << endl;
            moveX = hVector[specialId].x;
            moveY = hVector[specialId].y;
        }
        else if(id < humanCount)
        {
            cerr << "Toward human" << endl;
            moveX = hVector[id].x;
            moveY = hVector[id].y;
        }
        else
        {
            cerr << "Toward zombie" << endl;
            id = moveTowardZombie();
            cerr << "id = " << id << endl;
            if(id < zombieCount)
            {
                moveX = zVector[id].nextX;
                moveY = zVector[id].nextY;
            }
            else
            {
                moveX = zVector[0].nextX;
                moveY = zVector[0].nextY;
            }
        }
        
        cout << moveX << " " << moveY << endl; // Your destination coordinates
    }
}