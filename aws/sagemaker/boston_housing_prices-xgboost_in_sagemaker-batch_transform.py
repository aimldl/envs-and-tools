#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
boston_housing_prices-xgboost_in_sagemaker-batch_transform.py
## Udacity-Deep Learning Nanodegree Program

### Tutorials
Boston Housing (Batch Transform) - High Level
"""

"""
#### Predicting Boston Housing Prices Using XGBoost in SageMaker (Batch Transform)
##### Overview
Boston Housing Dataset is use to predict the median value of a home
  in the area of Boston, MA.

##### The Boston Housing Dataset  
https://www.cs.toronto.edu/~delve/data/boston/bostonDetail.html

##### The documentation for SageMaker's High Level Python API
Amazon SageMaker Python SDK
https://sagemaker.readthedocs.io/en/latest/

The project homepage
https://github.com/aws/sagemaker-python-sdk
"""

"""
##### General Outline
This tutorial covers steps 1 through 5.

1. Download or otherwise retrieve the data.
2. Process / Prepare the data.
3. Upload the processed data to S3.
4. Train a chosen model.
5. Test the trained model (typically using a batch transform job).
6. Deploy the trained model.
7. Use the deployed model.

#####
Number of Cases
    The dataset contains a total of 506 cases.
Variables
    There are 14 attributes in each case of the dataset. They are:

        CRIM - per capita crime rate by town
        ZN - proportion of residential land zoned for lots over 25,000 sq.ft.
        INDUS - proportion of non-retail business acres per town.
        CHAS - Charles River dummy variable (1 if tract bounds river; 0 otherwise)
        NOX - nitric oxides concentration (parts per 10 million)
        RM - average number of rooms per dwelling
        AGE - proportion of owner-occupied units built prior to 1940
        DIS - weighted distances to five Boston employment centres
        RAD - index of accessibility to radial highways
        TAX - full-value property-tax rate per $10,000
        PTRATIO - pupil-teacher ratio by town
        B - 1000(Bk - 0.63)^2 where Bk is the proportion of blacks by town
        LSTAT - % lower status of the population
        MEDV - Median value of owner-occupied homes in $1000's

boston.data.shape= (506, 13)
boston.target.shape= (506,)
"""
