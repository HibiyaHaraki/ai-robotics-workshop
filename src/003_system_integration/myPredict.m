classdef myPredict < matlab.System
  % Inference using Deep Neural Network

  % Public, tunable properties
  properties(Nontunable)
      MATFile = 'mynet_new.mat' % MAT-file for deep neural network object
  end

  properties(DiscreteState)

  end

  % Pre-computed constants
  properties(Access = private)
    mynet;
  end

  methods(Access = protected)
    function setupImpl(obj)
      % Perform one-time calculations, such as computing constants
      data = load(obj.MATFile);
      obj.mynet = data.trainedNet;
    end

    function y = stepImpl(obj,u)
      % Implement algorithm. Calculate y as a function of input u and
      % discrete states.
      y = obj.mynet.predict(u);
    end

    function resetImpl(obj)
      % Initialize / reset discrete-state properties
    end
    
    function out = getOutputDataTypeImpl(obj)
      out = "single";
    end
    function sz_1 = getOutputSizeImpl(obj)
      sz_1 = [1 2];
   end
  end

  methods(Access = protected, Static)
      function simMode = getSimulateUsingImpl
          % Return only allowed simulation mode in System block dialog
          simMode = "Interpreted execution";
      end
  end
end
