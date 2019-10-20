# MOSEK-MATLAB
## Introduction

- A COPY OF: MOSEK Optimization Toolbox for MATLAB. https://docs.mosek.com/9.0/toolbox/install-interface.html
- Personal academic license for mosek are free. https://www.mosek.com/products/academic-licenses/

## Installation

- `git clone https://github.com/star2dust/MOSEK-MATLAB.git`
- Setting up the paths: 
  ```matlab
  addpath('<MSKHOME>/mosek/9.0/toolbox/r2015a')
  ```

- or, if you do not want to overload functions such as [`linprog`](https://docs.mosek.com/9.0/toolbox/reference.html#linprog) and [`quadprog`](https://docs.mosek.com/9.0/toolbox/reference.html#quadprog) from the MATLAB Optimization Toolbox with their **MOSEK** versions, then write: 
  ```matlab
  addpath('<MSKHOME>/mosek/9.0/toolbox/r2015aom')
  ```

- You can verify that Optimization Toolbox for MATLAB works by executing

  ```matlab
  mosekdiag
  ```