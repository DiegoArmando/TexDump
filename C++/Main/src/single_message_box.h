#ifndef SINGLE_MESSAGE_BOX_H
#define SINGLE_MESSAGE_BOX_H

#include <QDialog>
#include "message.h"

namespace Ui {
class single_message_box;
}

class single_message_box : public QDialog
{
    Q_OBJECT

public:
    explicit single_message_box(QWidget *parent = 0);
    ~single_message_box();
	void set_message(Message message);

private slots:
    void on_copy_button_clicked();

    void on_close_button_clicked();

private:
    Ui::single_message_box *ui;
};

#endif // SINGLE_MESSAGE_BOX_H
