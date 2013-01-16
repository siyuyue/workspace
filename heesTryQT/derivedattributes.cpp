#include "derivedattributes.h"

DerivedAttributes::DerivedAttributes(QObject *parent) :
    QAbstractTableModel(parent)
{
}

int	DerivedAttributes::rowCount( const QModelIndex & parent) const
{
    if( parent.isValid() )
        return 0;
    return 2;
}

int	DerivedAttributes::columnCount( const QModelIndex & parent) const
{
    if( parent.isValid() )
        return 0;
    return 2;
}

QVariant DerivedAttributes::headerData( int section, Qt::Orientation orientation, int role) const
{
    if( role == Qt::DisplayRole )
    {
        if( orientation == Qt::Horizontal )
            if( section == 0 )
            {
                return tr("Name");
            }
            else if(section == 1)
            {
                return tr("Value");
            }
    }
    return QVariant();
}

QVariant DerivedAttributes::data( const QModelIndex & index, int role) const
{
    if( role != Qt::DisplayRole )
        return QVariant();

    if( index.column() == 0 )
        return 22;
    else
        return tr("Sam");
}

Qt::ItemFlags DerivedAttributes::flags ( const QModelIndex & index ) const
{
    return Qt::ItemIsEditable | Qt::ItemIsEnabled;
}

bool DerivedAttributes::setData ( const QModelIndex & index, const QVariant & value, int role)
{
    if( role != Qt::DisplayRole )
        return false;

    return true;
}
