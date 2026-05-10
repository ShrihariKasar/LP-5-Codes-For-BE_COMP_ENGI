# Assignment 9: Linear Regression using Deep Neural Network
# Implement Boston Housing Price Prediction using Deep Neural Network

import numpy as np
import pandas as pd
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense
from tensorflow.keras.datasets import boston_housing
from sklearn.preprocessing import StandardScaler
from sklearn.metrics import mean_squared_error

# Load Dataset
(X_train, y_train), (X_test, y_test) = boston_housing.load_data()

# Feature Scaling
scaler = StandardScaler()

X_train = scaler.fit_transform(X_train)
X_test = scaler.transform(X_test)

# Build Deep Neural Network Model
model = Sequential()

model.add(Dense(64, activation='relu', input_shape=(X_train.shape[1],)))
model.add(Dense(32, activation='relu'))
model.add(Dense(16, activation='relu'))

# Output Layer
model.add(Dense(1))

# Compile Model
model.compile(
    optimizer='adam',
    loss='mse',
    metrics=['mae']
)

# Train Model
history = model.fit(
    X_train,
    y_train,
    epochs=100,
    batch_size=16,
    validation_split=0.2,
    verbose=1
)

# Predict on Test Data
predictions = model.predict(X_test)

# Calculate Error
mse = mean_squared_error(y_test, predictions)

print("\nMean Squared Error:", mse)

# Display Some Predictions
print("\nActual Price vs Predicted Price\n")

for i in range(10):
    print(f"Actual: {y_test[i]:.2f}   Predicted: {predictions[i][0]:.2f}")