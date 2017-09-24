#include "softkeyboard.h"
#include "ui_softkeyboard.h"

softkeyboard::softkeyboard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::softkeyboard)
{
    ui->setupUi(this);
    init();

}

softkeyboard::~softkeyboard()
{
    delete ui;
}

void softkeyboard::init()
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);  //隐去窗口边框/并不在任务栏显示
    setAttribute(Qt::WA_TranslucentBackground, true);  //设置窗口背景透明
    return;
}

void softkeyboard::on_key_shift_clicked(bool checked)
{
    if (checked) {
        ui->key_0->setText(QString(")"));
        ui->key_1->setText(QString("!"));
        ui->key_2->setText(QString("@"));
        ui->key_3->setText(QString("#"));
        ui->key_4->setText(QString("$"));
        ui->key_5->setText(QString("%"));
        ui->key_6->setText(QString("^"));
        ui->key_7->setText(QString("&&"));
        ui->key_8->setText(QString("*"));
        ui->key_9->setText(QString("("));
        ui->key_a->setText(QString("A"));
        ui->key_b->setText(QString("B"));
        ui->key_c->setText(QString("C"));
        ui->key_d->setText(QString("D"));
        ui->key_e->setText(QString("E"));
        ui->key_f->setText(QString("F"));
        ui->key_g->setText(QString("G"));
        ui->key_h->setText(QString("H"));
        ui->key_i->setText(QString("I"));
        ui->key_j->setText(QString("J"));
        ui->key_k->setText(QString("K"));
        ui->key_l->setText(QString("L"));
        ui->key_m->setText(QString("M"));
        ui->key_n->setText(QString("N"));
        ui->key_o->setText(QString("O"));
        ui->key_p->setText(QString("P"));
        ui->key_q->setText(QString("Q"));
        ui->key_r->setText(QString("R"));
        ui->key_s->setText(QString("S"));
        ui->key_t->setText(QString("T"));
        ui->key_u->setText(QString("U"));
        ui->key_v->setText(QString("V"));
        ui->key_w->setText(QString("W"));
        ui->key_x->setText(QString("X"));
        ui->key_y->setText(QString("Y"));
        ui->key_z->setText(QString("Z"));
        ui->key_point->setText(QString("~"));
        ui->key_sub->setText(QString("_"));
        ui->key_equ->setText(QString("+"));
        ui->key_bracket_left->setText(QString("{"));
        ui->key_bracket_right->setText(QString("}"));
        ui->key_slash_left->setText(QString("?"));
        ui->key_slash_right->setText(QString("|"));
        ui->key_semicolon->setText(QString(":"));
        ui->key_quotes->setText(QString("\""));
        ui->key_comma->setText(QString("<"));
        ui->key_dot->setText(QString(">"));
    }
    else {
        ui->key_0->setText(QString("0"));
        ui->key_1->setText(QString("1"));
        ui->key_2->setText(QString("2"));
        ui->key_3->setText(QString("3"));
        ui->key_4->setText(QString("4"));
        ui->key_5->setText(QString("5"));
        ui->key_6->setText(QString("6"));
        ui->key_7->setText(QString("7"));
        ui->key_8->setText(QString("8"));
        ui->key_9->setText(QString("9"));
        ui->key_a->setText(QString("a"));
        ui->key_b->setText(QString("b"));
        ui->key_c->setText(QString("c"));
        ui->key_d->setText(QString("d"));
        ui->key_e->setText(QString("e"));
        ui->key_f->setText(QString("f"));
        ui->key_g->setText(QString("g"));
        ui->key_h->setText(QString("h"));
        ui->key_i->setText(QString("i"));
        ui->key_j->setText(QString("j"));
        ui->key_k->setText(QString("k"));
        ui->key_l->setText(QString("l"));
        ui->key_m->setText(QString("m"));
        ui->key_n->setText(QString("n"));
        ui->key_o->setText(QString("o"));
        ui->key_p->setText(QString("p"));
        ui->key_q->setText(QString("q"));
        ui->key_r->setText(QString("r"));
        ui->key_s->setText(QString("s"));
        ui->key_t->setText(QString("t"));
        ui->key_u->setText(QString("u"));
        ui->key_v->setText(QString("v"));
        ui->key_w->setText(QString("w"));
        ui->key_x->setText(QString("x"));
        ui->key_y->setText(QString("y"));
        ui->key_z->setText(QString("z"));
        ui->key_point->setText(QString("`"));
        ui->key_sub->setText(QString("-"));
        ui->key_equ->setText(QString("="));
        ui->key_bracket_left->setText(QString("["));
        ui->key_bracket_right->setText(QString("]"));
        ui->key_slash_left->setText(QString("/"));
        ui->key_slash_right->setText(QString("\\"));
        ui->key_semicolon->setText(QString(";"));
        ui->key_quotes->setText(QString("'"));
        ui->key_comma->setText(QString(","));
        ui->key_dot->setText(QString("."));
    }
    return;
}

void softkeyboard::on_key_caps_lock_clicked(bool checked)
{
    if (checked) {
        ui->key_a->setText(QString("A"));
        ui->key_b->setText(QString("B"));
        ui->key_c->setText(QString("C"));
        ui->key_d->setText(QString("D"));
        ui->key_e->setText(QString("E"));
        ui->key_f->setText(QString("F"));
        ui->key_g->setText(QString("G"));
        ui->key_h->setText(QString("H"));
        ui->key_i->setText(QString("I"));
        ui->key_j->setText(QString("J"));
        ui->key_k->setText(QString("K"));
        ui->key_l->setText(QString("L"));
        ui->key_m->setText(QString("M"));
        ui->key_n->setText(QString("N"));
        ui->key_o->setText(QString("O"));
        ui->key_p->setText(QString("P"));
        ui->key_q->setText(QString("Q"));
        ui->key_r->setText(QString("R"));
        ui->key_s->setText(QString("S"));
        ui->key_t->setText(QString("T"));
        ui->key_u->setText(QString("U"));
        ui->key_v->setText(QString("V"));
        ui->key_w->setText(QString("W"));
        ui->key_x->setText(QString("X"));
        ui->key_y->setText(QString("Y"));
        ui->key_z->setText(QString("Z"));
    }
    else {
        ui->key_a->setText(QString("a"));
        ui->key_b->setText(QString("b"));
        ui->key_c->setText(QString("c"));
        ui->key_d->setText(QString("d"));
        ui->key_e->setText(QString("e"));
        ui->key_f->setText(QString("f"));
        ui->key_g->setText(QString("g"));
        ui->key_h->setText(QString("h"));
        ui->key_i->setText(QString("i"));
        ui->key_j->setText(QString("j"));
        ui->key_k->setText(QString("k"));
        ui->key_l->setText(QString("l"));
        ui->key_m->setText(QString("m"));
        ui->key_n->setText(QString("n"));
        ui->key_o->setText(QString("o"));
        ui->key_p->setText(QString("p"));
        ui->key_q->setText(QString("q"));
        ui->key_r->setText(QString("r"));
        ui->key_s->setText(QString("s"));
        ui->key_t->setText(QString("t"));
        ui->key_u->setText(QString("u"));
        ui->key_v->setText(QString("v"));
        ui->key_w->setText(QString("w"));
        ui->key_x->setText(QString("x"));
        ui->key_y->setText(QString("y"));
        ui->key_z->setText(QString("z"));
    }
    return;
}

