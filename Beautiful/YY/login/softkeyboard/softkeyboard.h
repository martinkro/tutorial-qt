#ifndef SOFTKEYBOARD_H
#define SOFTKEYBOARD_H

#include <QWidget>

namespace Ui {
class softkeyboard;
}

class softkeyboard : public QWidget
{
    Q_OBJECT
    
public:
    explicit softkeyboard(QWidget *parent = 0);
    ~softkeyboard();
    
private slots:
    void on_key_shift_clicked(bool checked);
    void on_key_caps_lock_clicked(bool checked);

    void on_key_0_clicked();
    void on_key_1_clicked();
    void on_key_2_clicked();
    void on_key_3_clicked();
    void on_key_4_clicked();
    void on_key_5_clicked();
    void on_key_6_clicked();
    void on_key_7_clicked();
    void on_key_8_clicked();
    void on_key_9_clicked();
    void on_key_a_clicked();
    void on_key_b_clicked();
    void on_key_c_clicked();
    void on_key_d_clicked();
    void on_key_e_clicked();
    void on_key_f_clicked();
    void on_key_g_clicked();
    void on_key_h_clicked();
    void on_key_i_clicked();
    void on_key_j_clicked();
    void on_key_k_clicked();
    void on_key_l_clicked();
    void on_key_m_clicked();
    void on_key_n_clicked();
    void on_key_o_clicked();
    void on_key_p_clicked();
    void on_key_q_clicked();
    void on_key_r_clicked();
    void on_key_s_clicked();
    void on_key_t_clicked();
    void on_key_u_clicked();
    void on_key_v_clicked();
    void on_key_w_clicked();
    void on_key_x_clicked();
    void on_key_y_clicked();
    void on_key_z_clicked();
    void on_key_point_clicked();
    void on_key_sub_clicked();
    void on_key_equ_clicked();
    void on_key_bracket_left_clicked();
    void on_key_bracket_right_clicked();
    void on_key_slash_left_clicked();
    void on_key_slash_right_clicked();
    void on_key_semicolon_clicked();
    void on_key_quotes_clicked();
    void on_key_comma_clicked();
    void on_key_dot_clicked();
    void on_key_del_clicked();  //ÍË¸ñ°´Å¥

signals:
    void input(QString str);

private:
    Ui::softkeyboard *ui;

    void init();
};

#endif // SOFTKEYBOARD_H
