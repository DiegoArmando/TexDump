#ifndef MULTI_MESSAGE_BOX_H
#define MULTI_MESSAGE_BOX_H

#include <QWidget>
#include <QClipboard>
#include "message.h"

namespace Ui {
class multi_message_box;
}

class multi_message_box : public QWidget
{
    Q_OBJECT

public:
    explicit multi_message_box(QWidget *parent = 0);
    ~multi_message_box();

	void set_message(Message message, int num_messages);

private slots:
    void on_close_button_clicked();

    void on_copy_button_clicked();

    void on_log_button_clicked();

private:
  Ui::multi_message_box *ui;
  QClipboard *clipboard;
};

#endif // MULTI_MESSAGE_BOX_H
