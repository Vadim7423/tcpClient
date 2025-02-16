#ifndef VOLT_METEERS_MODEL_H
#define VOLT_METEERS_MODEL_H

#include <QAbstractListModel>
#include "channel.h"

class VoltMeteersModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum ModelRoles {
        NameRole = Qt::UserRole + 1,
        HighLimitRole,
        LowLimitRole,
        StatusRole,
        ValRole,
        RangeRole
    };

    explicit VoltMeteersModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void addItem(Channel* channel);

    void clear();

    void setStatus(int channel_id, Channel::Status status);

    Channel::Status status(int channel_id) const;

    void setValue(int channel_id, float value);

signals:
    void reseted();

protected:
    void reset();
    QHash<int, QByteArray> roleNames() const override;

private:
    std::vector<std::shared_ptr<Channel>> m_data;

};

#endif // VOLT_METEERS_MODEL_H
