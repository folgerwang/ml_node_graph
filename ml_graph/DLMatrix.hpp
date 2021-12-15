#pragma once

#include <QtGui/QPixmap>

#include <nodes/NodeDataModel>

using QtNodes::NodeData;
using QtNodes::NodeDataType;

enum MatrixFormat{
    kFloat,
    kInt8,
};

/// The class can potentially incapsulate any user data which
/// need to be transferred within the Node Editor graph
class DLMatrixData : public NodeData
{
public:

  DLMatrixData() {}

  NodeDataType
  type() const override
  {
    //       id      name
    return {"matrix", "m"};
  }

  void*
  matrix() const { return matrix_->data(); }

private:
    uint32_t    w_;
    uint32_t    h_;
    uint32_t    d_;

    MatrixFormat    format_;
    std::shared_ptr<std::vector<uint8_t>> matrix_;
};
