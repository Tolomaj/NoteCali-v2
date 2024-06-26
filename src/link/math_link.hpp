/*********************************************************************
 * @file  math_link.hpp
 * @author Ondřej Gross (xgross13)
 *
 * @brief comunication between objects
 * Platform independent way to comunicate between math solver and math presenter
 *********************************************************************/

/// @brief template for Math solver
class MathSolver{
    public: virtual void solve();
};


/// @brief template for Math presenter
class MathPresenter{
    public: virtual void present();
    public: virtual void highlite();
};


/// @brief comunicaction for mathematics betwen GUI and solver
class math_link {
    MathPresenter * presenter;
    MathSolver * solver;
public:



    void setPresenter(MathPresenter * presenter){
        this->presenter = presenter;
    };

    void setSolver( MathSolver * solver){
        this->solver = solver;
    };

    /// @brief send signal with lines to solve
    void reqest_solve(){
        if(solver != nullptr){ solver->solve(); }
    }

    /// @brief send solution to calculator signal
    void reqest_publish(){
        if(presenter != nullptr){ presenter->present(); }
    }

    /// @brief send text to input box signal (future feature to highlite texts)
    void reqest_highlite(){
        if(presenter != nullptr){ presenter->highlite(); }
    }
};