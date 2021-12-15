#pragma once

#include <QtCore/QObject>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QLabel>

#include <nodes/NodeDataModel>

#include <iostream>

using QtNodes::PortType;
using QtNodes::PortIndex;
using QtNodes::NodeData;
using QtNodes::NodeDataType;
using QtNodes::NodeDataModel;
using QtNodes::NodeValidationState;

class IntegerData;

class MaxPoolingModel
  : public NodeDataModel
{
  Q_OBJECT

public:
  MaxPoolingModel() = default;

  virtual
  ~MaxPoolingModel() = default;

public:

  QString
  caption() const override
  { return QStringLiteral("Max Pooling"); }

  bool
  captionVisible() const override
  { return true; }

  bool
  portCaptionVisible(PortType, PortIndex ) const override
  { return true; }

  QString
  portCaption(PortType portType, PortIndex portIndex) const override
  {
    switch (portType)
    {
      case PortType::In:
        if (portIndex == 0)
          return QStringLiteral("src data");
        else if (portIndex == 1)
          return QStringLiteral("max pool params");

        break;

      case PortType::Out:
        return QStringLiteral("dst data");

      default:
        break;
    }
    return QString();
  }

  QString
  name() const override
  { return QStringLiteral("Max Pooling"); }

public:

  QJsonObject
  save() const override;

public:

  unsigned int
  nPorts(PortType portType) const override;

  NodeDataType
  dataType(PortType portType, PortIndex portIndex) const override;

  std::shared_ptr<NodeData>
  outData(PortIndex port) override;

  void
  setInData(std::shared_ptr<NodeData>, int) override;

  QWidget *
  embeddedWidget() override { return nullptr; }

  NodeValidationState
  validationState() const override;

  QString
  validationMessage() const override;

private:

  std::shared_ptr<NodeData> _src_data;
  std::weak_ptr<IntegerData> _number2;

  std::shared_ptr<NodeData> _dst_data;

  NodeValidationState modelValidationState = NodeValidationState::Warning;
  QString modelValidationError = QStringLiteral("Missing or incorrect inputs");
};
