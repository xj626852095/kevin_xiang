///:
/*****************************************************************************
 **                                                                         **
 **                               .======.                                  **
 **                               | INRI |                                  **
 **                               |      |                                  **
 **                               |      |                                  **
 **                      .========'      '========.                         **
 **                      |   _      xxxx      _   |                         **
 **                      |  /_;-.__ / _\  _.-;_\  |                         **
 **                      |     `-._`'`_/'`.-'     |                         **
 **                      '========.`\   /`========'                         **
 **                               | |  / |                                  **
 **                               |/-.(  |                                  **
 **                               |\_._\ |                                  **
 **                               | \ \`;|                                  **
 **                               |  > |/|                                  **
 **                               | / // |                                  **
 **                               | |//  |                                  **
 **                               | \(\  |                                  **
 **                               |  ``  |                                  **
 **                               |      |                                  **
 **                               |      |                                  **
 **                               |      |                                  **
 **                               |      |                                  **
 **                   \\    _  _\\| \//  |//_   _ \// _                     **
 **                  ^ `^`^ ^`` `^ ^` ``^^`  `^^` `^ `^                     **
 **                                                                         **
 **                    Copyright © 1997-2013 by Tong G.                     **
 **                          ALL RIGHTS RESERVED.                           **
 **                                                                         **
 ****************************************************************************/

#include "Calculator.h"

#include <QTextBrowser>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QLayout>
#include <QString>
#include <QChar>
#include <QIcon>
#include <QMessageBox>
//.._Calculator类实现

    /* 构造函数实现 */
    _Calculator::_Calculator(QWidget *_Parent)
        : QDialog(_Parent)
        {
        m_TypeNameLabel = new QLabel(tr("输入姓名(&N):"));
        m_NameLineEdit = new QLineEdit;
        m_TypeNameLabel->setBuddy(m_NameLineEdit);
        connect(m_NameLineEdit, SIGNAL(textChanged(QString)),
                this, SLOT(_LineEditChanged(QString)));

        m_CalculateButton = new QPushButton(tr("计算"));
        m_CalculateButton->setIcon(QIcon(":/icon/calculator.ico"));
        m_CalculateButton->setEnabled(false);
        connect(m_CalculateButton, SIGNAL(clicked()),
                this, SLOT(_CalculateButtonClicked()));

        m_DisplayValBrowser = new QTextBrowser;

        m_CloseButton = new QPushButton(tr("关闭(&C)"));
        m_CloseButton->setIcon(QIcon(":/icon/close.ico"));
        m_AboutButton = new QPushButton(tr("关于(&A)..."));
        m_AboutButton->setIcon(QIcon(":/icon/about.ico"));
        connect(m_CloseButton, SIGNAL(clicked()), this, SLOT(close()));
        connect(m_AboutButton, SIGNAL(clicked()), this, SLOT(_AboutButtonClieked()));

        QHBoxLayout* _TypeNameLayout = new QHBoxLayout;
        _TypeNameLayout->addWidget(m_TypeNameLabel);
        _TypeNameLayout->addWidget(m_NameLineEdit);
        _TypeNameLayout->addWidget(m_CalculateButton);

        QHBoxLayout* _BottomLayout = new QHBoxLayout;
        _BottomLayout->addStretch();
        _BottomLayout->addWidget(m_AboutButton);
        _BottomLayout->addWidget(m_CloseButton);

        QVBoxLayout* _MainLayout = new QVBoxLayout;
        _MainLayout->addLayout(_TypeNameLayout);
        _MainLayout->addWidget(m_DisplayValBrowser);
        _MainLayout->addLayout(_BottomLayout);

        setLayout(_MainLayout);
        setFixedSize(300, 400);
        setWindowTitle(tr("人品计算器"));
        setWindowIcon(QIcon(":/icon/icon.ico"));
        }

    /////////////////////////////////////////////////////////////////////////
    //..protected部分

    /* _LineEditChanged()槽实现 */
    void _Calculator::_LineEditChanged(QString _TesterName)
        {
        m_CalculateButton->setEnabled(!_TesterName.isEmpty());
        }

    /* _CalculateButtonClicked()槽实现
     * 根据用户输入的姓名计算人品得分
     * 基本算法:将姓名的各个字符的unicode码值相加, 然后去mod 100
     */
    void _Calculator::_CalculateButtonClicked()
        {
        QString _Name = m_NameLineEdit->text();
        int _Score = 0; // 记录人品分数

        const QChar* _AfterTransform = _Name.unicode(); // 将_Name转换成unicode形式
        for (int _Index = 0; _Index < _Name.count(); _Index++)
            // 将_Name中的每个字符的Unicode码值相加
            _Score += (_AfterTransform + _Index)->unicode();
        _Score %= 100;  // 将相加的结果取模, 即得出人品指数

        if (_Score <= 100 && _Score >= 95)
            {
            m_DisplayValBrowser->setText(
                        QObject::tr("<h1><font color = green><i>%1</font></i>的人品指数：<font color = green>%2</font>"
                                    "<h4>点评：人品中的祖师爷级别，人品高至如此，夫复何求？"
                                    "<h1><font color = gray>代表人物：孔老夫子</h1></font>"
                                    "<img src=\":/images/KFZ.jpg\">"
                                    ).arg(_Name).arg(_Score));
            }
        else if (_Score < 95 && _Score >= 90)
            {
            m_DisplayValBrowser->setText(
                        QObject::tr("<h1><font color = green><i>%1</font></i>人品指数：<font color = green>%2</font>"
                                    "<h4>点评：运气超好，老婆超多的好人品。"
                                    "<h2><font color = gray>代表人物：韦小宝</font>"
                                    "<img src=\":/images/WXB.jpg\">"
                                    ).arg(_Name).arg(_Score));

            }
        else if (_Score < 90 && _Score >= 85)
            {
            m_DisplayValBrowser->setText(
                        QObject::tr("<h1><font color = green><i>%1</font></i>人品指数：<font color = green>%2</font>"
                                    "<h4>点评：正义与力量的结合，精忠报国不解释。"
                                    "<h2><font color = gray>代表人物：岳飞</font>"
                                    "<img src=\":/images/YF.jpg\">"
                                    ).arg(_Name).arg(_Score));

            }
        else if (_Score < 85 && _Score >= 70)
            {
            m_DisplayValBrowser->setText(
                        QObject::tr("<h1><font color = green><i>%1</font></i>的人品指数：<font color = blue>%2</font>"
                                    "<h4>点评：还不错，你还算是正直，不知元芳怎么看？"
                                    "<h2><font color = gray>代表人物：狄仁杰</font>"
                                    "<img src=\":/images/DRJ.jpg\">"
                                    ).arg(_Name).arg(_Score));
            }
        else if (_Score < 70 && _Score >= 65)
            {
            m_DisplayValBrowser->setText(
                        QObject::tr("<h1><font color = green><i>%1</font></i>的人品指数：<font color = blue>%2</font>"
                                    "<h4>点评：算不上坏人，但有时为达目的不择手段，"
                                    "就像他，虽为一代明君，但也曾为了皇位手足相残。"
                                    "<h2><font color = gray>代表人物：李世民</font>"
                                    "<img src=\":/images/LSM.jpg\">"
                                    ).arg(_Name).arg(_Score));
            }
        else if (_Score < 65 && _Score >= 50)
            {
            m_DisplayValBrowser->setText(
                        QObject::tr("<h1><font color = green><i>%1</font></i>的人品指数：<font color = orange>%2</font>"
                                    "<h4>点评：诶，怎么说你呢，偷东西也就算了，"
                                    "别偷人啊。节操呢？你的节操呢？！"
                                    "<h2><font color = gray>代表人物：西门大官人</font>"
                                    "<img src=\":/images/XMQ.jpg\">"
                                    ).arg(_Name).arg(_Score));
            }
        else if (_Score < 55 && _Score >= 40)
            {
            m_DisplayValBrowser->setText(
                        QObject::tr("<h1><font color = green><i>%1</font></i>的人品指数：<font color = orange>%2</font>"
                                    "<h4>点评：奸雄，实实在在的奸雄，宁可我负人人，不可人人负我，"
                                    "你的人品不及格，小心哦。"
                                    "<h2><font color = gray>代表人物：曹操</font>"
                                    "<img src=\":/images/CC.jpg\">"
                                    ).arg(_Name).arg(_Score));
            }
        else if (_Score < 40 && _Score >= 25)
            {
            m_DisplayValBrowser->setText(
                        QObject::tr("<h1><font color = green><i>%1</font></i>的人品指数：<font color = red>%2</font>"
                                    "<h4>点评：算了，和你没有什么人品好谈的~~~"
                                    "<h2><font color = gray>代表人物：秦桧</font>"
                                    "<img src=\":/images/QH.jpg\">"
                                    ).arg(_Name).arg(_Score));
            }
        else if (_Score < 25)
            {
            m_DisplayValBrowser->setText(
                        QObject::tr("<h1><font color = green><i>%1</font></i>的人品指数：<font color = red>%2</font>"
                                    "<h4>点评：心理扭曲，极度扭曲，极度~~扭曲~~操！"
                                    "<h2><font color = gray>代表人物：药家鑫</font>"
                                    "<h4>这么久了，大家一直在思索，为什么你捅了死者8刀，而不是7刀，也不是9刀,"
                                    "为何偏偏是8刀?后来一次音乐课上我突然明白了，你是弹钢琴的，所以一刀下去，心中就有了节奏："
                                    "“哆唻咪发嗦啦唏哆”，正好八刀，一刀下去就收不住了"
                                    "<img src=\":/images/YJX.jpg\">"
                                    ).arg(_Name).arg(_Score));
            }
        }

    /* _AboutButtonClicked()槽实现 */
    void _Calculator::_AboutButtonClieked()
        {
        QMessageBox::about(this, tr("About Character Calculator"),
             tr("<h1>Character Calculator 1.0</h1>"

             "<p><h4>Release 1.0</h4>"
             "<p>Copyright &copy; 1997-2013 Domino Inc. & Tong G. "
             "All rights reserved."
             "<p>版权所有 © 1997-2013 Domino Inc. & 郭桐。 保留所有权利。"
             "<p>警告：本计算机程序受著作权法和国际公约的保护，未经授权擅自复制或传播本程序"
             "的部分或全部，可能受到严厉的民事及刑事制裁，并将在法律许可的范围内受到最大"
             "可能的起诉。"
             ));
        }

/////////////////////////////////////////////////////////////////////////////

/****************************************************************************
 **                                                                        **
 **      _________                                      _______            **
 **     |___   ___|                                   / ______ \           **
 **         | |     _______   _______   _______      | /      |_|          **
 **         | |    ||     || ||     || ||     ||     | |    _ __           **
 **         | |    ||     || ||     || ||     ||     | |   |__  \          **
 **         | |    ||     || ||     || ||     ||     | \_ _ __| |  _       **
 **         |_|    ||_____|| ||     || ||_____||      \________/  |_|      **
 **                                           ||                           **
 **                                    ||_____||                           **
 **                                                                        **
 ***************************************************************************/
///:~
