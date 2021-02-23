#ifndef MENU_SCOREWINDOW_H
#define MENU_SCOREWINDOW_H

#include <QtWidgets/QMainWindow>

namespace Ui {
    class ScoreWindow;
}

class ScoreWindow: public QMainWindow {
    Q_OBJECT;

    private:
        Ui::ScoreWindow *ui;

    private:
        std::vector<std::pair<int, std::vector<std::string>>> sortMapByHighScore(std::map<std::string,
                                                                                 std::vector<int>> names);
        void setTable();
        void setTableData(std::vector<std::pair<int, std::vector<std::string>>> scores);
        void addPlayer(std::string name, std::string kills, std::string bullets, std::string score);
        void setStyle();

    public:
        ScoreWindow(QWidget *parent = 0, std::map<std::string, std::vector<int>> names = {});
        ~ScoreWindow();
};


#endif //MENU_SCOREWINDOW_H
