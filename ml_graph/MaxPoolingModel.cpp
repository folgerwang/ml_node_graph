#include "MaxPoolingModel.hpp"
#include "DLMatrix.hpp"

#include <QtGui/QDoubleValidator>

#include "IntegerData.hpp"
#include "PixmapData.hpp"

QJsonObject
MaxPoolingModel::
save() const
{
  QJsonObject modelJson;

  modelJson["name"] = name();

  return modelJson;
}


unsigned int
MaxPoolingModel::
nPorts(PortType portType) const
{
  unsigned int result = 1;

  switch (portType)
  {
    case PortType::In:
      result = 2;
      break;

    case PortType::Out:
      result = 1;

    default:
      break;
  }

  return result;
}


NodeDataType
MaxPoolingModel::
dataType(PortType port_type, PortIndex port_index) const
{
    auto result = IntegerData().type();
    if (port_type == PortType::In) {
        if (port_index == 0) {
            result = PixmapData().type();
        }
    }
    else if (port_type == PortType::Out) {
        if (port_index == 0) {
            result = PixmapData().type();
        }
    }
  return result;
}


std::shared_ptr<NodeData>
MaxPoolingModel::
outData(PortIndex)
{
  return _dst_data;
}


void
MaxPoolingModel::
setInData(std::shared_ptr<NodeData> data, PortIndex portIndex)
{
  auto numberData =
    std::dynamic_pointer_cast<IntegerData>(data);

  if (portIndex == 0)
  {
    _src_data = data;
    _dst_data = _src_data;
  }
  else
  {
    _number2 = numberData;
  }

  PortIndex const outPortIndex = 0;
#if 0
  {
    auto n1 = _number1.lock();
    auto n2 = _number2.lock();

    if (n2 && (n2->number() == 0.0))
    {
      modelValidationState = NodeValidationState::Error;
      modelValidationError = QStringLiteral("Division by zero error");
      _result.reset();
    }
    else if (n1 && n2)
    {
      modelValidationState = NodeValidationState::Valid;
      modelValidationError = QString();
      _result = std::make_shared<IntegerData>(n1->number() %
                                              n2->number());
    }
    else
    {
      modelValidationState = NodeValidationState::Warning;
      modelValidationError = QStringLiteral("Missing or incorrect inputs");
      _result.reset();
    }
  }
#endif
  Q_EMIT dataUpdated(outPortIndex);
}


NodeValidationState
MaxPoolingModel::
validationState() const
{
  return modelValidationState;
}


QString
MaxPoolingModel::
validationMessage() const
{
  return modelValidationError;
}
