/****************************************************************************
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the demonstration applications of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial Usage
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Nokia.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights.  These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef SCENE_H
#define SCENE_H

//#include <GL/glew.h>
#include "glextensions.h"

#include <QtGui>
#include <QtOpenGL>

#include "roundedbox.h"
#include "gltrianglemesh.h"
#include "vector.h"
#include "trackball.h"
#include "glbuffers.h"
#include "glshaders.h"
#include "qtbox.h"

#define PI 3.14159265358979

class ParameterEdit : public QWidget
{
public:
    virtual void emitChange() = 0;
};

class ColorEdit : public ParameterEdit
{
    Q_OBJECT
public:
    ColorEdit(QRgb initialColor, int id);
    QRgb color() const {return m_color;}
    virtual void emitChange() {emit colorChanged(m_color, m_id);}
public slots:
    void editDone();
signals:
    void colorChanged(QRgb color, int id);
protected:
    virtual void mousePressEvent(QMouseEvent *event);
    void setColor(QRgb color); // also emits colorChanged()
private:
    QGraphicsScene *m_dialogParentScene;
    QLineEdit *m_lineEdit;
    QFrame *m_button;
    QRgb m_color;
    int m_id;
};

class FloatEdit : public ParameterEdit
{
    Q_OBJECT
public:
    FloatEdit(float initialValue, int id);
    float value() const {return m_value;}
    virtual void emitChange() {emit valueChanged(m_value, m_id);}
public slots:
    void editDone();
signals:
    void valueChanged(float value, int id);
private:
    QGraphicsScene *m_dialogParentScene;
    QLineEdit *m_lineEdit;
    float m_value;
    int m_id;
};

class GraphicsWidget : public QGraphicsProxyWidget
{
protected:
    virtual QVariant itemChange(GraphicsItemChange change, const QVariant &value);
    virtual void resizeEvent(QGraphicsSceneResizeEvent *event);
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

class TwoSidedGraphicsWidget : public QObject
{
    Q_OBJECT
public:
    TwoSidedGraphicsWidget(QGraphicsScene *scene);
    void setWidget(int index, QWidget *widget);
    QWidget *widget(int index);
public slots:
    void flip();
protected slots:
    void animateFlip();
private:
    GraphicsWidget *m_proxyWidgets[2];
    int m_current;
    int m_angle; // angle in degrees
    int m_delta;
};

class RenderOptionsDialog : public QDialog
{
    Q_OBJECT
public:
    RenderOptionsDialog();
    int addTexture(const QString &name);
    int addShader(const QString &name);
    void emitParameterChanged();
protected slots:
    void setColorParameter(QRgb color, int id);
    void setFloatParameter(float value, int id);
signals:
    void dynamicCubemapToggled(int);
    void colorParameterChanged(const QString &, QRgb);
    void floatParameterChanged(const QString &, float);
    void textureChanged(int);
    void shaderChanged(int);
    void doubleClicked();
protected:
    virtual void mouseDoubleClickEvent(QMouseEvent *event);

    QVector<QByteArray> m_parameterNames;
    QComboBox *m_textureCombo;
    QComboBox *m_shaderCombo;
    QVector<ParameterEdit *> m_parameterEdits;
};

class ItemDialog : public QDialog
{
    Q_OBJECT
public:
    enum ItemType {
        QtBoxItem,
        CircleItem,
        SquareItem,
    };

    ItemDialog();
public slots:
    void triggerNewQtBox();
    void triggerNewCircleItem();
    void triggerNewSquareItem();
signals:
    void doubleClicked();
    void newItemTriggered(ItemDialog::ItemType type);
protected:
    virtual void mouseDoubleClickEvent(QMouseEvent *event);
};

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    Scene(int width, int height, int maxTextureSize);
    ~Scene();
    virtual void drawBackground(QPainter *painter, const QRectF &rect);

public slots:
    void setShader(int index);
    void setTexture(int index);
    void toggleDynamicCubemap(int state);
    void setColorParameter(const QString &name, QRgb color);
    void setFloatParameter(const QString &name, float value);
    void newItem(ItemDialog::ItemType type);
protected:
    void renderBoxes(const gfx::Matrix4x4f &view, int excludeBox = -2);
    void setStates();
    void setLights();
    void defaultStates();
    void renderCubemaps();

    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    virtual void wheelEvent(QGraphicsSceneWheelEvent * event);
private:
    void initGL();
    QPointF pixelPosToViewPos(const QPointF& p);

    QTime m_time;
    int m_lastTime;
    int m_mouseEventTime;
    int m_distExp;
    int m_frame;
    int m_maxTextureSize;

    int m_currentShader;
    int m_currentTexture;
    bool m_dynamicCubemap;
    bool m_updateAllCubemaps;

    RenderOptionsDialog *m_renderOptions;
    ItemDialog *m_itemDialog;
    QTimer *m_timer;
    GLRoundedBox *m_box;
    TrackBall m_trackBalls[3];
    QVector<GLTexture *> m_textures;
    GLTextureCube *m_environment;
    GLTexture3D *m_noise;
    GLRenderTargetCube *m_mainCubemap;
    QVector<GLRenderTargetCube *> m_cubemaps;
    QVector<GLProgram *> m_programs;
    GLVertexShader *m_vertexShader;
    QVector<GLFragmentShader *> m_fragmentShaders;
    GLFragmentShader *m_environmentShader;
    GLProgram *m_environmentProgram;
};



#endif
