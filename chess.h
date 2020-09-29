#ifndef CHESS_H
#define CHESS_H
#include <vector>
// 游戏类型
enum Type
{
    PERSON,
    AI
};

// 游戏状态
enum status
{
    PLAYING,
    WIN,
    LOSE
};


class chess
{
public:
    chess();

public:
    bool player;// 标示下棋方
    Type gameType;
    std::vector<std::vector<int>> mapGV;// 空白为0，黑子1，白子-1
    std::vector<std::vector<int>> mapSV;// 存储各个点位的评分情况
    status status;
    void clear();
    bool isFour(int row,int col);
    bool isFive(int row,int col);
    int fourCount=0,fiveCount=0;
    void actAIAfter(int &row, int &col);
    void start(Type type); // 开始游戏
    void actAI(int &row, int &col); // 机器执行下棋
    void updateMap(int row, int col);
    bool winorlose(int row, int col); //判断输赢
    void cScore();
    void cScore1();
    bool isDead();//判断是否和棋
};

#endif // GAMEMODEL_H



