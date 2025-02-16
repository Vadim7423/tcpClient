#include "volt_meteers_model.h"
#include <QQmlEngine>

VoltMeteersModel::VoltMeteersModel(QObject *parent)
    : QAbstractListModel(parent)
{
    QJSEngine::setObjectOwnership(this, QJSEngine::ObjectOwnership::CppOwnership);
    connect(this, &VoltMeteersModel::reseted, this, &VoltMeteersModel::reset);
}

int VoltMeteersModel::rowCount(const QModelIndex &parent) const
{
    return m_data.size();
}

QVariant VoltMeteersModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= m_data.size())
        return QVariant();

    auto channel = m_data[index.row()].get();

    static std::unordered_map<float, int> ranges {
        {0.001, 0},
        {1, 1},
        {1000, 2},
        {1000000, 3}
    };

    switch(role) {
    case HighLimitRole:
        return channel->range().max();
    case LowLimitRole:
        return channel->range().min();
    case StatusRole:
        return QVariant::fromValue(channel->status());
    case ValRole:
        return channel->value();
    case RangeRole:
        return ranges[channel->range().max()];
    }

    return QVariant();
}

void VoltMeteersModel::addItem(Channel *channel)
{
    m_data.emplace_back(channel);
    emit reseted();
}

void VoltMeteersModel::clear()
{
    m_data.clear();
    emit reseted();
}

void VoltMeteersModel::setStatus(int channel_id, Channel::Status status)
{
    m_data[channel_id]->setStatus(status);
    QModelIndex model_ind = index(channel_id);
    emit dataChanged(model_ind, model_ind, {StatusRole});
}

Channel::Status VoltMeteersModel::status(int channel_id) const
{
    return m_data[channel_id]->status();
}

void VoltMeteersModel::setValue(int channel_id, float value)
{
    m_data[channel_id]->setValue(value);
    QModelIndex model_ind = index(channel_id);
    emit dataChanged(model_ind, model_ind, {ValRole});
}

void VoltMeteersModel::reset()
{
    beginResetModel();
    endResetModel();
}

QHash<int, QByteArray> VoltMeteersModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[StatusRole] = "status";
    roles[HighLimitRole] = "highlimit";
    roles[LowLimitRole] = "lowlimit";
    roles[RangeRole] = "range";
    roles[ValRole] = "val";
    return roles;
}
