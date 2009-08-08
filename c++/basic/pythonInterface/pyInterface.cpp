
#include "../../finance/instruments/bond/coupon.h"
#include "../../finance/instruments/bond/bond.h"
#include "../../finance/curve/forwardrate.h"

#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>

namespace bp = boost::python;

struct Coupon_wrapper : Coupon, bp::wrapper< Coupon > {

    Coupon_wrapper(Coupon const & arg )
    : Coupon( arg )
      , bp::wrapper< Coupon >(){
        // copy constructor
        
    }

    Coupon_wrapper(double const value, double const maturity )
    : Coupon( value, maturity )
      , bp::wrapper< Coupon >(){
        // constructor
    
    }

    virtual double getSortItem(  ) const  {
        if( bp::override func_getSortItem = this->get_override( "getSortItem" ) )
            return func_getSortItem(  );
        else
            return this->Coupon::getSortItem(  );
    }
    
    
    double default_getSortItem(  ) const  {
        return Coupon::getSortItem( );
    }

};

BOOST_PYTHON_MODULE(libAnalyttlic){
    { //::std::vector<Coupon,std::allocator<Coupon> >
        typedef bp::class_< std::vector<Coupon,std::allocator<Coupon> > > vCouponExposer_t;
        vCouponExposer_t vCouponExposer = vCouponExposer_t( "vCoupon" );
        bp::scope vCoupon( vCouponExposer );
        vCouponExposer.def( bp::vector_indexing_suite< ::std::vector<Coupon,std::allocator<Coupon> > >() );
    }
    
    { //::std::vector<Cartesian2D<double>,std::allocator<Cartesian2D<double> > >
        typedef bp::class_< std::vector<Cartesian2D<double>,std::allocator<Cartesian2D<double> > > > dSetCartesian2DExposer_t;
        dSetCartesian2DExposer_t dSetCartesian2DExposer = dSetCartesian2DExposer_t( "dSetCartesian2D" );
        bp::scope dSetCartesian2D_scope( dSetCartesian2DExposer );
        dSetCartesian2DExposer.def( bp::vector_indexing_suite< ::std::vector<Cartesian2D<double>,std::allocator<Cartesian2D<double> > > >() );
    }

    { //::std::vector<Bond,std::allocator<Bond> >
        typedef bp::class_< std::vector<Bond,std::allocator<Bond> > > vBondExposer_t;
        vBondExposer_t vBondExposer = vBondExposer_t( "vBond" );
        bp::scope vBond( vBondExposer );
        vBondExposer.def( bp::vector_indexing_suite< ::std::vector<Bond,std::allocator<Bond> > >() );
    }

    { //::Bond
        typedef bp::class_< Bond, boost::noncopyable > Bond_exposer_t;
        Bond_exposer_t Bond_exposer = Bond_exposer_t( "Bond", bp::init< double, std::vector<Coupon,std::allocator<Coupon> > const & >(( bp::arg("marketPrice"), bp::arg("_coupons") )) );
        bp::scope Bond_scope( Bond_exposer );
        Bond_exposer.def( bp::init< Bond const & >(( bp::arg("other") )) );
        { //::Bond::duration
        
            typedef double ( ::Bond::*duration_function_type )( double ) const;
            
            Bond_exposer.def( 
                "duration"
                , duration_function_type( &::Bond::duration )
                , ( bp::arg("r") ) );
        
        }
        { //::Bond::maturityIfCouponsAreSorted
        
            typedef double ( ::Bond::*maturityIfCouponsAreSorted_function_type )(  ) const;
            
            Bond_exposer.def( 
                "maturityIfCouponsAreSorted"
                , maturityIfCouponsAreSorted_function_type( &::Bond::maturityIfCouponsAreSorted ) );
        
        }
        { //::Bond::numberOfCoupons
        
            typedef int ( ::Bond::*numberOfCoupons_function_type )(  ) const;
            
            Bond_exposer.def( 
                "numberOfCoupons"
                , numberOfCoupons_function_type( &::Bond::numberOfCoupons ) );
        
        }
        { //::Bond::operator=
        
            typedef ::Bond & ( ::Bond::*assign_function_type )( ::Bond const & ) ;
            
            Bond_exposer.def( 
                "assign"
                , assign_function_type( &::Bond::operator= )
                , ( bp::arg("other") )
                , bp::return_self< >() );
        
        }
        { //::Bond::printCoupons
        
            typedef void ( ::Bond::*printCoupons_function_type )(  ) const;
            
            Bond_exposer.def( 
                "printCoupons"
                , printCoupons_function_type( &::Bond::printCoupons ) );
        
        }
        { //::Bond::sortCouponsByDate
        
            typedef void ( ::Bond::*sortCouponsByDate_function_type )(  ) ;
            
            Bond_exposer.def( 
                "sortCouponsByDate"
                , sortCouponsByDate_function_type( &::Bond::sortCouponsByDate ) );
        
        }
        { //::Bond::test
        
            typedef void ( ::Bond::*test_function_type )(  ) ;
            
            Bond_exposer.def( 
                "test"
                , test_function_type( &::Bond::test ) );
        
        }
        { //::Bond::ytm
        
            typedef double ( ::Bond::*ytm_function_type )(  ) const;
            
            Bond_exposer.def( 
                "ytm"
                , ytm_function_type( &::Bond::ytm ) );
        
        }
        Bond_exposer.def_readwrite( "marketPrice", &Bond::marketPrice );
        Bond_exposer.def_readwrite( "givenYield", &Bond::givenYield );
    }

    bp::class_< Coupon_wrapper >( "Coupon", bp::init< double, double >(( bp::arg("value"), bp::arg("maturity") )) )    
        .def( 
            "getMaturity"
            , &::Coupon::getMaturity )    
        .def( 
            "getSortItem"
            , &::Coupon::getSortItem
            , &Coupon_wrapper::default_getSortItem )    
        .def( 
            "getValue"
            , &::Coupon::getValue )    
        .def( 
            "pv"
            , &::Coupon::pv
            , ( bp::arg("r") ) );
    
    
    bp::class_< CurveBase >( "CurveBase" )    
            .def( 
                "bootstrap"
                , (void ( ::CurveBase::* )( ::InterpolationFactoryBase const &,double,double,double ) )( &::CurveBase::bootstrap )
                , ( bp::arg("interpolationFactory"), bp::arg("first_x"), bp::arg("last_x"), bp::arg("increment") ) )    
            .def( 
                "bootstrap"
                , (void ( ::CurveBase::* )( ::InterpolationFactoryBase const &,double ) )( &::CurveBase::bootstrap )
                , ( bp::arg("interpolationFactory"), bp::arg("increment") ) )    
            .def( 
                "bootstrap"
                , (void ( ::CurveBase::* )( ::InterpolationBase *,double ) )( &::CurveBase::bootstrap )
                , ( bp::arg("interpolationScheme"), bp::arg("increment") ) )    
            .def( 
                "cubicSplineBootstrap"
                , &::CurveBase::cubicSplineBootstrap
                , ( bp::arg("increment") ) )    
            .def( 
                "dividedDifferenceBootstrap"
                , &::CurveBase::dividedDifferenceBootstrap
                , ( bp::arg("increment") ) )    
            .def( 
                "printInterpolatedPoints"
                , &::CurveBase::printInterpolatedPoints )    
            .def( 
                "printPoints"
                , &::CurveBase::printPoints )    
            .def_readwrite( "interpolatedPoints", &CurveBase::interpolatedPoints )    
            .def_readwrite( "points", &CurveBase::points )
            .def("pyListInterpolatedPoints", &CurveBase::pyListInterpolatedPoints )
            .def("pyListOriginalPoints", &CurveBase::pyListOriginalPoints );

        bp::class_< ForwardRate >( "ForwardRate", bp::init< double, double >(( bp::arg("time"), bp::arg("rate") )) )    
            .def_readwrite( "rate", &ForwardRate::rate )    
            .def_readwrite( "time", &ForwardRate::time );

        bp::class_< ForwardRateCurve, bp::bases< CurveBase > >( "ForwardRateCurve", bp::init< std::vector<Bond,std::allocator<Bond> > & >(( bp::arg("_bonds") )) )    
            .def( 
                "sortBondsByMaturity"
                , &::ForwardRateCurve::sortBondsByMaturity );

        bp::implicitly_convertible< std::vector<Bond,std::allocator<Bond> > &, ForwardRateCurve >();
    

}

