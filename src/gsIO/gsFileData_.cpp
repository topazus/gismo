#include <gsCore/gsTemplateTools.h>

#include <gsIO/gsFileData.h>
#include <gsIO/gsFileData.hpp>

#ifdef GISMO_WITH_PYBIND11
#include <gsCore/gsMultiPatch.h>
#include <gsCore/gsMultiBasis.h>
#include <gsNurbs/gsBSpline.h>
#include <gsNurbs/gsTensorBSpline.h>

#include <gsPde/gsBoundaryConditions.h>
#include <gsCore/gsFunctionExpr.h>
#include <gsIO/gsOptionList.h>
#include <gsMatrix/gsSparseMatrix.h>
#endif


namespace gismo
{

  CLASS_TEMPLATE_INST gsFileData<real_t>;

#ifdef GISMO_WITH_PYBIND11

gsMatrix<real_t> getMatrix(std::string & filename)
{
    gsFileData<> file;
    file.read(filename);
    gsMatrix<real_t> result;
    file.getAnyFirst(result);
    return result;
}

namespace py = pybind11;
  void pybind11_init_gsFileData(py::module &m) {

    using Class = gsFileData<real_t>;
    py::class_<Class> fd(m, "gsFileData");

    fd.def(py::init<>())
      .def(py::init<const std::string&>())
      
      .def("read", &Class::read)
      .def("clear", &Class::clear)
      .def("numData", &Class::numData)
      .def("save",           &Class::save,           py::arg("fname")="dump", py::arg("compress")=false)
      .def("saveCompressed", &Class::saveCompressed, py::arg("fname")="dump")
      .def("dump",           &Class::dump,           py::arg("fname")="dump")

      .def("addComment", &Class::addComment)
      .def("lastPath", &Class::lastPath)
      .def("setFloatPrecision", &Class::setFloatPrecision)
      .def("getFloatPrecision", &Class::getFloatPrecision)

      // .def("getId", static_cast<const gsBasis<real_t> & (Class::*)(const size_t) const > (&Class::getId))
      .def("getId", static_cast<void (Class::*)(const int &, gsMultiPatch<real_t> &) const > (&Class::getId<gsMultiPatch<real_t>>), "Gets a const reference to basis with index i")
      .def("getId", static_cast<void (Class::*)(const int &, gsGeometry<real_t> &) const > (&Class::getId<gsGeometry<real_t>>), "Gets a const reference to basis with index i")


      .def("add", static_cast<void (Class::*)(const gsMultiPatch<real_t> &, int) > (&Class::add<gsMultiPatch<real_t>>), py::arg("object"), py::arg("id")=-1, "Add gsMultiPatch to the filedata.")
      .def("add", static_cast<void (Class::*)(const gsMultiBasis<real_t> &, int) > (&Class::add<gsMultiBasis<real_t>>), py::arg("object"), py::arg("id")=-1, "Add gsMultiBasis to the filedata.")
      .def("add", static_cast<void (Class::*)(const gsBSpline<real_t> &, int) > (&Class::add<gsBSpline<real_t>>), py::arg("object"), py::arg("id")=-1, "Add gsBSpline to the filedata.")
      .def("add", static_cast<void (Class::*)(const gsTensorBSpline<2, real_t> &, int) > (&Class::add<gsTensorBSpline<2, real_t>>), py::arg("object"), py::arg("id")=-1, "Add gsTensorBSpline to the filedata.")

      .def("add", static_cast<void (Class::*)(const gsBoundaryConditions<real_t> &, int) > (&Class::add<gsBoundaryConditions<real_t>>), py::arg("object"), py::arg("id")=-1, "Add gsBoundaryConditions to the filedata.")
      .def("add", static_cast<void (Class::*)(const gsFunctionExpr<real_t> &, int) > (&Class::add<gsFunctionExpr<real_t>>), py::arg("object"), py::arg("id")=-1, "Add gsFunctionExpr to the filedata.")
      .def("add", static_cast<void (Class::*)(const gsOptionList &, int) > (&Class::add<gsOptionList>), py::arg("object"), py::arg("id")=-1, "Add gsOptionList to the filedata.")
      .def("add", static_cast<void (Class::*)(const gsMatrix<real_t> &, int) > (&Class::add<gsMatrix<real_t>>), py::arg("object"), py::arg("id")=-1, "Add gsMatrix to the filedata.")
      .def("add", static_cast<void (Class::*)(const gsSparseMatrix<real_t> &, int) > (&Class::add<gsSparseMatrix<real_t>>), py::arg("object"), py::arg("id")=-1, "Add gsSparseMatrix to the filedata.")

      //.def("addSparse", static_cast<void (Class::*)(const gsSparseMatrix<real_t> &) > (&Class::add<gsSparseMatrix<real_t>>), "Add gsSparseMatrix to the filedata.")
      
      .def("getAnyFirst", static_cast<bool (Class::*)(gsMultiPatch<real_t> &) const > (&Class::getAnyFirst<gsMultiPatch<real_t>>), "Get gsMultiPatch to the filedata.")
      .def("getAll", static_cast<std::vector< memory::unique_ptr<gsGeometry<real_t>> > (Class::*)() const > (&Class::getAll<gsGeometry<real_t>>), "Get gsGeometry to the filedata.")

      // Work around to obtain the matrix from Filedata. Standard way is not working!
      .def("getMatrix", &getMatrix, "Get any first gsMatrix.")

      .def("bufferSize", &Class::bufferSize)
      .def("print", &Class::print)
      .def("contents", &Class::contents)
      .def("numTags", &Class::numTags)
      

      // .def("getId", (void (gsFileData<real_t>::*)(const int&, Object&)) &Class::getId<Object>)

      .def("__repr__",
           [](const gsFileData<> &obj) {
             std::stringstream os;
             os << obj;
             return os.str();
           })
      ;    
  }
#endif // GISMO_WITH_PYBIND11
} // end namespace gismo
