#ifndef CHORUSKIT_TREECONFIGWIDGET_H
#define CHORUSKIT_TREECONFIGWIDGET_H

#include "QPushButton"
#include "QTreeWidget"
#include <QCheckBox>
#include <QComboBox>
#include <QHBoxLayout>
#include <QJsonArray>
#include <QJsonObject>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>

namespace TemplatePlg {
    namespace Internal {
        class TreeConfigWidget : public QWidget {
            Q_OBJECT
        public:
            explicit TreeConfigWidget(QString configPath, bool configGen = false, QWidget *parent = nullptr);
            ~TreeConfigWidget();

        protected:
            QString configPath;
            QString developConfigPath;
            bool configGen;

            QTreeWidget *m_treeWidget;
            QVBoxLayout *mainLayout;
            QLineEdit *m_name;
            QLineEdit *m_enName;
            QLineEdit *m_value;
            QComboBox *m_childType;
            QComboBox *m_type;
            QPushButton *m_up;
            QPushButton *m_down;
            QPushButton *m_addButton;
            QPushButton *m_removeButton;
            QPushButton *m_saveButton;
            QPushButton *m_loadButton;

        private:
            QString getLocalLanguage();
            QJsonArray readJsonFile(QString filePath);
            QJsonObject itemToJson(QTreeWidgetItem *item);
            QJsonArray createJsonFromTree(QTreeWidgetItem *item = nullptr);
            void loadConfig(const QJsonArray &config, int insertIndex = -1, QTreeWidgetItem *parent = nullptr);

        private slots:
            void addTableRow();
            void removeTableRow();
            void createConfig();
            bool saveConfig();
            void on_btnUp_clicked();
            void on_btnDown_clicked();
        };

    }
}
#endif // CHORUSKIT_TREECONFIGWIDGET_H