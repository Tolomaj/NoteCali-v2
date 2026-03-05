//Todo this file is wrote by ai help. 
//todo extensive rewiew needed

#pragma once

#include <QtWidgets>
#include <functional>
#include <vector>
#include "../../link/settings_link.hpp"

class HorizontalWheelArea : public QScrollArea {
public:
    explicit HorizontalWheelArea(QWidget *parent = nullptr) : QScrollArea(parent) {}

protected:
    void wheelEvent(QWheelEvent *event) override {
        int delta = event->angleDelta().x();
        if (delta == 0) {
            delta = event->angleDelta().y();
        }

        if (delta != 0) {
            QScrollBar *bar = this->horizontalScrollBar();
            bar->setValue(bar->value() - delta);
            event->accept();
            return;
        }

        QScrollArea::wheelEvent(event);
    }
};

class ShortcutHelperBar : public QFrame {
private:
    struct OperationItem {
        QString text;
        QString iconPngPath;
        QString beforeCursor;
        QString afterCursor;
        bool isSettingsAction = false;
    };

    QHBoxLayout *rootLayout;
    QToolButton *toggleButton;
    HorizontalWheelArea *scrollArea;
    QWidget *scrollContent;
    QHBoxLayout *scrollLayout;

    QTextEdit *editor = nullptr;
    std::function<void()> onSettings;
    QWidget *bodyWidget = nullptr;
    bool minimized = false;
    bool collapsible = true;
    bool docked = false;
    int sizeLevel = 10;
    int overlayHeight = 34;
    int overlayMargin = 6;
    int buttonSide = 18;
    int scrollHeight = 22;
    int iconPx = 14;
    int cornerRadius = 7;
    bool applyingThemeVisual = false;
    bool startupCollapseApplied = false;
    QGraphicsDropShadowEffect *elevationEffect = nullptr;

    int scaled(int base, float factor, int minValue = 1) const {
        return qMax(minValue, qRound(base * factor));
    }

    void applySizing() {
        float factor = static_cast<float>(sizeLevel) / 10.0f;

        overlayHeight = scaled(34, factor, 18);
        overlayMargin = scaled(6, factor, 2);
        buttonSide = scaled(18, factor, 10);
        scrollHeight = scaled(22, factor, 12);
        iconPx = scaled(14, factor, 8);
        cornerRadius = scaled(7, factor, 3);

        int spacing = scaled(4, factor, 1);
        int marginX = scaled(6, factor, 2);
        int marginY = scaled(4, factor, 2);
        this->setFixedHeight(overlayHeight);
        if (rootLayout != nullptr) {
            rootLayout->setSpacing(spacing);
            rootLayout->setContentsMargins(marginX, marginY, marginX, marginY);
        }
        if (scrollArea != nullptr) {
            scrollArea->setFixedHeight(scrollHeight);
        }
        if (toggleButton != nullptr) {
            toggleButton->setFixedSize(buttonSide, buttonSide);
        }

        if (scrollLayout != nullptr) {
            for (int i = 0; i < scrollLayout->count(); i++) {
                QLayoutItem *item = scrollLayout->itemAt(i);
                if (item == nullptr || item->widget() == nullptr) {
                    continue;
                }
                QToolButton *btn = qobject_cast<QToolButton*>(item->widget());
                if (btn == nullptr) {
                    continue;
                }
                btn->setFixedHeight(buttonSide);
                btn->setIconSize(QSize(iconPx, iconPx));
            }
        }

        applyThemeVisual();
    }

    void applyThemeVisual() {
        if (applyingThemeVisual) {
            return;
        }
        applyingThemeVisual = true;

        QPalette pal = QApplication::palette(this);
        QColor bg = pal.color(QPalette::Window);
        QColor border = pal.color(QPalette::Mid);

        if (elevationEffect != nullptr) {
            elevationEffect->setEnabled(!docked);
        }

        if (docked) {
            bg.setAlpha(255);
            border.setAlpha(220);
            this->setStyleSheet(
                QString(
                    "#ShortcutHelperBar {"
                    " background-color: rgba(%1, %2, %3, %4);"
                    " border: none;"
                    " border-top: 1px solid rgba(%5, %6, %7, %8);"
                    " border-radius: 0px;"
                    "}"
                )
                    .arg(bg.red()).arg(bg.green()).arg(bg.blue()).arg(bg.alpha())
                    .arg(border.red()).arg(border.green()).arg(border.blue()).arg(border.alpha())
            );
        } else {
            int bgAlpha = 220;
            bg.setAlpha(bgAlpha);
            border.setAlpha(210);
            this->setStyleSheet(
                QString(
                    "#ShortcutHelperBar {"
                    " background-color: rgba(%1, %2, %3, %4);"
                    " border: 1px solid rgba(%5, %6, %7, %8);"
                    " border-radius: %9px;"
                    "}"
                )
                    .arg(bg.red()).arg(bg.green()).arg(bg.blue()).arg(bg.alpha())
                    .arg(border.red()).arg(border.green()).arg(border.blue()).arg(border.alpha())
                    .arg(cornerRadius)
            );

            if (elevationEffect != nullptr) {
                QColor shadow = pal.color(QPalette::Shadow);
                shadow.setAlpha(120);
                elevationEffect->setColor(shadow);
                elevationEffect->setBlurRadius(16.0);
                elevationEffect->setOffset(0.0, 2.0);
            }
        }

        applyingThemeVisual = false;
    }

    void setButtonVisual(QToolButton *btn, const OperationItem &item) {
        if (!item.iconPngPath.isEmpty()) {
            QPixmap pix(item.iconPngPath);
            if (!pix.isNull()) {
                btn->setText("");
                btn->setIcon(QIcon(pix));
                btn->setIconSize(QSize(iconPx, iconPx));
                return;
            }
        }
        btn->setIcon(QIcon());
        btn->setText(item.text);
    }

    void insertToEditor(const QString &beforeCursor, const QString &afterCursor) {
        if (editor == nullptr) {
            return;
        }

        QTextCursor cursor = editor->textCursor();
        cursor.beginEditBlock();
        cursor.insertText(beforeCursor + afterCursor);
        if (!afterCursor.isEmpty()) {
            cursor.movePosition(QTextCursor::Left, QTextCursor::MoveAnchor, afterCursor.size());
        }
        cursor.endEditBlock();

        editor->setTextCursor(cursor);
        editor->setFocus();
    }

    void addMathButton(const OperationItem &item) {
        QToolButton *btn = new QToolButton(scrollContent);
        setButtonVisual(btn, item);
        btn->setCursor(Qt::PointingHandCursor);
        btn->setAutoRaise(true);
        connect(btn, &QToolButton::clicked, this, [this, item]() {
            if (item.isSettingsAction) {
                if (onSettings) {
                    onSettings();
                }
                return;
            }
            this->insertToEditor(item.beforeCursor, item.afterCursor);
        });
        scrollLayout->addWidget(btn);
    }

    void refreshMinimizedState() {
        if (!collapsible) {
            minimized = false;
            scrollArea->setVisible(true);
            toggleButton->setVisible(false);
            return;
        }

        toggleButton->setVisible(true);
        scrollArea->setVisible(!minimized);
        toggleButton->setText(minimized ? ">>" : "<<");
    }

    bool isDockedInHostLayout() const {
        if (bodyWidget == nullptr) {
            return false;
        }

        QWidget *host = bodyWidget->parentWidget();
        QBoxLayout *hostLayout = (host != nullptr) ? qobject_cast<QBoxLayout*>(host->layout()) : nullptr;
        if (hostLayout == nullptr) {
            return false;
        }

        return hostLayout->indexOf(const_cast<ShortcutHelperBar*>(this)) >= 0;
    }

    void applyDockingParent() {
        if (bodyWidget == nullptr) {
            return;
        }

        QWidget *host = bodyWidget->parentWidget();
        QBoxLayout *hostLayout = (host != nullptr) ? qobject_cast<QBoxLayout*>(host->layout()) : nullptr;

        if (docked) {
            if (host == nullptr || hostLayout == nullptr) {
                return;
            }

            if (this->parentWidget() != host) {
                this->setParent(host);
            }

            int currentIndex = hostLayout->indexOf(this);
            if (currentIndex != 0) {
                if (currentIndex >= 0) {
                    hostLayout->removeWidget(this);
                }
                hostLayout->insertWidget(0, this);
            }
            return;
        }

        if (hostLayout != nullptr && hostLayout->indexOf(this) >= 0) {
            hostLayout->removeWidget(this);
        }

        QWidget *floatingHost = (host != nullptr) ? host : bodyWidget;
        if (this->parentWidget() != floatingHost) {
            this->setParent(floatingHost);
        }
    }

public:
    explicit ShortcutHelperBar(QWidget *parent = nullptr) : QFrame(parent) {
        this->setObjectName("ShortcutHelperBar");
        this->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Fixed);
        this->setMinimumWidth(0);
        this->setFixedHeight(overlayHeight);
        this->setFrameShape(QFrame::NoFrame);
        this->setFrameShadow(QFrame::Plain);
        this->setLineWidth(0);
        this->setAutoFillBackground(true);
        this->setBackgroundRole(QPalette::Window);

        elevationEffect = new QGraphicsDropShadowEffect(this);
        this->setGraphicsEffect(elevationEffect);

        rootLayout = new QHBoxLayout(this);
        rootLayout->setSpacing(4);
        rootLayout->setContentsMargins(6, 4, 6, 4);

        scrollArea = new HorizontalWheelArea(this);
        scrollArea->setWidgetResizable(true);
        scrollArea->setFrameStyle(QFrame::NoFrame);
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scrollArea->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Fixed);
        scrollArea->setMinimumWidth(0);
        scrollArea->setFixedHeight(22);

        scrollContent = new QWidget(scrollArea);
        scrollLayout = new QHBoxLayout(scrollContent);
        scrollLayout->setSpacing(2);
        scrollLayout->setContentsMargins(0, 0, 0, 0);
        scrollLayout->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        scrollLayout->setSizeConstraint(QLayout::SetNoConstraint);
        scrollContent->setLayout(scrollLayout);
        scrollArea->setWidget(scrollContent);
        rootLayout->addWidget(scrollArea, 1);

        toggleButton = new QToolButton(this);
        toggleButton->setCursor(Qt::PointingHandCursor);
        toggleButton->setAutoRaise(true);
        toggleButton->setFixedSize(18, 18);
        rootLayout->addWidget(toggleButton, 0, Qt::AlignRight);
        connect(toggleButton, &QToolButton::clicked, this, [this]() {
            if (!collapsible) {
                return;
            }
            minimized = !minimized;
            refreshMinimizedState();
            this->updatePlacement();
        });

        const std::vector<OperationItem> operations = {
            {"⚙", "", "", "", true},

            {"€[]", "", "€[", "]", false},
            {"to", "", " to ", "", false},
            {"&", "", "&", "", false},
            {"#", "", "#", "", false},
            {":", "", ":", "", false},

            {";sum", "", ";sum", "", false},
            {";rstsum", "", ";rstsum", "", false},
            {";sumbreak", "", ";sumbreak", "", false},
            {";clear", "", ";clear", "", false},
            {";rand", "", ";rand", "", false},
            {";randi", "", ";randi", "", false},
            {";randn", "", ";randn", "", false},

            {"r[];", "", "r[", "];", false},
            {"b[];", "", "b[", "];", false},
            {"c;", "", "c;", "", false},
            {"h;", "", "h;", "", false},

            {"+", "", " + ", "", false},
            {"-", "", " - ", "", false},
            {"*", "", " * ", "", false},
            {"/", "", " / ", "", false},
            {"%", "", "%", "", false},
            {"^", "", "^", "", false},
            {"<", "", "<", "", false},
            {">", "", ">", "", false},
            {"<=", "", "<=", "", false},
            {">=", "", ">=", "", false},
            {"==", "", "==", "", false},
            {"!=", "", "!=", "", false},
            {"&&", "", "&&", "", false},
            {"||", "", "||", "", false},
            {"=", "", " = ", "", false},

            {"sin(x)", "", "sin(", ")", false},
            {"cos(x)", "", "cos(", ")", false},
            {"tan(x)", "", "tan(", ")", false},
            {"cot(x)", "", "cot(", ")", false},
            {"degtodeg(x)", "", "degtodeg(", ")", false},
            {"degtorad(x)", "", "degtorad(", ")", false},
            {"radtodeg(x)", "", "radtodeg(", ")", false},
            {"asin(x)", "", "asin(", ")", false},
            {"acos(x)", "", "acos(", ")", false},
            {"atan(x)", "", "atan(", ")", false},
            {"acot(x)", "", "acot(", ")", false},
            {"sinh(x)", "", "sinh(", ")", false},
            {"cosh(x)", "", "cosh(", ")", false},
            {"tanh(x)", "", "tanh(", ")", false},
            {"coth(x)", "", "coth(", ")", false},
            {"asinh(x)", "", "asinh(", ")", false},
            {"acosh(x)", "", "acosh(", ")", false},
            {"atanh(x)", "", "atanh(", ")", false},
            {"acoth(x)", "", "acoth(", ")", false},
            {"ln(x)", "", "ln(", ")", false},
            {"log(x,base)", "", "log(", ",)", false},
            {"exp(x)", "", "exp(", ")", false},
            {"abs(x)", "", "abs(", ")", false},
            {"sgn(x)", "", "sgn(", ")", false},
            {"round(x)", "", "round(", ")", false},
            {"int(x)", "", "int(", ")", false},
            {"ceil(x)", "", "ceil(", ")", false},
            {"floor(x)", "", "floor(", ")", false},
            {"frac(x)", "", "frac(", ")", false},
            {"factorial(x)", "", "factorial(", ")", false},
            {"gamma(x)", "", "gamma(", ")", false},
            {"sqrt(x)", "assets/3rot.png", "sqrt(", ")", false},
            {"root(x;index)", "", "root(", ";)", false},
            {"mod(x;y)", "", "mod(", ";)", false},
            {"if(cond;t;f)", "", "if(", ";;)", false},
            {"or(x;y)", "", "or(", ";)", false},
            {"and(x;y)", "", "and(", ";)", false},
            {"not(x)", "", "not(", ")", false},
            {"bitor(x;y)", "", "bitor(", ";)", false},
            {"bitand(x;y)", "", "bitand(", ";)", false},
            {"bitxor(x;y)", "", "bitxor(", ";)", false}
        };

        for (const OperationItem &entry : operations) {
            addMathButton(entry);
        }

        applySizing();

        refreshMinimizedState();
        applyThemeVisual();

        if (qApp != nullptr) {
            qApp->installEventFilter(this);
        }
    }

    ~ShortcutHelperBar() override {
        if (qApp != nullptr) {
            qApp->removeEventFilter(this);
        }
    }

    QSize minimumSizeHint() const override {
        return QSize(0, overlayHeight);
    }

    void setEditor(QTextEdit *targetEditor) {
        editor = targetEditor;
    }

    void setSettingsAction(std::function<void()> callback) {
        onSettings = std::move(callback);
    }

    void attachToBody(QWidget *body) {
        bodyWidget = body;
        if (bodyWidget != nullptr && this->parentWidget() == nullptr) {
            this->setParent(bodyWidget);
        }
        applyDockingParent();
    }

    void setCollapsible(bool enabled) {
        collapsible = enabled;
        refreshMinimizedState();
        applyThemeVisual();
        this->updatePlacement();
    }

    void setSizeLevel(int level) {
        sizeLevel = qBound(1, level, 20);
        applySizing();
        this->updatePlacement();
    }

    void setDocked(bool enabled) {
        docked = enabled;
        applyThemeVisual();
        applyDockingParent();
        this->updatePlacement();
    }

    void syncFromSettings(SettingsLinkAP *settings) {
        if (settings == nullptr) {
            return;
        }

        int toolbarSize = settings->getInt("ToolBarSize");
        QString toolbarMode = QString::fromStdWString(settings->getWString("ToolBar")).trimmed().toUpper();
        bool showToolbar = (toolbarMode != "HIDDEN");
        bool useCollapsibleMode = (toolbarMode != "SHOWN");
        bool startCollapsedMode = (toolbarMode == "COLAPSABLE");
        bool showDocked = (toolbarMode == "SHOWN");

        if (!startupCollapseApplied) {
            if (startCollapsedMode) {
                minimized = true;
            }
            startupCollapseApplied = true;
        }

        this->setSizeLevel(toolbarSize);
        this->setCollapsible(useCollapsibleMode);
        this->setDocked(showDocked);
        this->setVisible(showToolbar);
        this->updatePlacement();
    }

    void updatePlacement() {
        if (bodyWidget == nullptr) {
            return;
        }

        applyDockingParent();

        if (!this->isVisible()) {
            return;
        }

        if (isDockedInHostLayout()) {
            return;
        }

        QWidget *host = this->parentWidget();
        if (host == nullptr) {
            return;
        }

        this->placeAtBottom(bodyWidget->width(), bodyWidget->height());
        QPoint origin = bodyWidget->mapTo(host, QPoint(0, 0));
        this->move(origin.x() + this->x(), origin.y() + this->y());
        this->raise();
    }

protected:
    bool eventFilter(QObject *watched, QEvent *event) override {
        if (watched == qApp && event != nullptr) {
            if (event->type() == QEvent::ApplicationPaletteChange ||
                event->type() == QEvent::ThemeChange ||
                event->type() == QEvent::StyleChange) {
                applyThemeVisual();
            }
        }

        return QFrame::eventFilter(watched, event);
    }

    void changeEvent(QEvent *event) override {
        QFrame::changeEvent(event);
        if (event->type() == QEvent::PaletteChange ||
            event->type() == QEvent::ApplicationPaletteChange ||
            event->type() == QEvent::ThemeChange) {
            applyThemeVisual();
        }
    }

    int margin() const {
        return overlayMargin;
    }

    void placeAtBottom(int parentWidth, int parentHeight) {
        int minWidth = buttonSide + (overlayMargin * 2);
        int widthWhenExpanded = qMax(buttonSide * 5, parentWidth - (2 * overlayMargin));
        int finalWidth = minimized ? minWidth : widthWhenExpanded;
        int x = overlayMargin;
        int y = parentHeight - overlayHeight - overlayMargin;

        this->setGeometry(x, y, finalWidth, overlayHeight);
    }
};
