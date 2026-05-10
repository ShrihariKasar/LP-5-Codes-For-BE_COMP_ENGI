# Assignment 12: Use MNIST Fashion Dataset and Create a Classifier
# Classify Fashion Clothing into Different Categories using Deep Neural Network

import numpy as np

from tensorflow.keras.datasets import fashion_mnist
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense, Flatten, Dropout

# Load Fashion MNIST Dataset
(X_train, y_train), (X_test, y_test) = fashion_mnist.load_data()

# Normalize Pixel Values
X_train = X_train / 255.0
X_test = X_test / 255.0

# Fashion Category Labels
fashion_labels = [
    "T-shirt/Top",
    "Trouser",
    "Pullover",
    "Dress",
    "Coat",
    "Sandal",
    "Shirt",
    "Sneaker",
    "Bag",
    "Ankle Boot"
]

# Build Deep Neural Network Model
model = Sequential()

# Convert 2D Image into 1D Vector
model.add(Flatten(input_shape=(28, 28)))

# Hidden Layers
model.add(Dense(256, activation='relu'))
model.add(Dropout(0.3))

model.add(Dense(128, activation='relu'))
model.add(Dropout(0.3))

model.add(Dense(64, activation='relu'))

# Output Layer (10 Classes)
model.add(Dense(10, activation='softmax'))

# Compile Model
model.compile(
    optimizer='adam',
    loss='sparse_categorical_crossentropy',
    metrics=['accuracy']
)

# Display Model Summary
print("\nModel Summary:\n")
model.summary()

# Train Model
history = model.fit(
    X_train,
    y_train,
    epochs=10,
    batch_size=64,
    validation_split=0.2,
    verbose=1
)

# Evaluate Model
loss, accuracy = model.evaluate(X_test, y_test)

print("\nTest Accuracy:", accuracy)

# Predict Sample Image
prediction = model.predict(X_test[:1])

predicted_class = np.argmax(prediction)

print("\nPredicted Category:",
      fashion_labels[predicted_class])

# Display Actual Category
print("Actual Category:",
      fashion_labels[y_test[0]])