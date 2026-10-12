# Route Configuration

## Topology

```text
         2.0.0.0              1.0.0.0              3.0.0.0
PC1 [f0/0] --- [f0/0] R1 [s1/1] --- [s1/0] R2 [f0/0] --- [f0/0] PC2
          Ether                 PPP                 Ether
```

## Configuration

Change to `config` mode.

```
Router> enable
Router# configure
Router(config)#
```

### IP Address Configure

#### PC1 f0/0

```
Router(config)# interface f0/0
Router(config-if)# ip add 2.1.1.1 255.0.0.0
Router(config-if)# no shutdown
```

#### R1 f0/0

```
Router(config)# interface f0/0
Router(config-if)# ip add 2.1.1.2 255.0.0.0
Router(config-if)# no shutdown
```

#### R2 f0/0

```
Router(config)# interface f0/0
Router(config-if)# ip add 3.1.1.1 255.0.0.0
Router(config-if)# no shutdown
```

#### PC2 f0/0

```
Router(config)# interface f0/0
Router(config-if)# ip add 3.1.1.2 255.0.0.0
Router(config-if)# no shutdown
```

#### R1 s1/1

```
Router(config)# interface s1/1
Router(config-if)# clock rate 115200
Router(config-if)# encapsulation ppp
Router(config-if)# ip add 1.1.1.1 255.0.0.0
Router(config-if)# no shutdown
```

#### R2 s1/0

```
Router(config)# interface s1/0
Router(config-if)# clock rate 115200
Router(config-if)# encapsulation ppp
Router(config-if)# ip add 1.1.1.2 255.0.0.0
Router(config-if)# no shutdown
```

### Route Configure

#### Static Route

##### PC1

```
Router(config)# ip route 3.0.0.0 255.0.0.0 f0/0
```

##### R1

```
Router(config)# ip route 3.0.0.0 255.0.0.0 s1/1
```

##### R2

```
Router(config)# ip route 2.0.0.0 255.0.0.0 s1/0
```

##### PC2

```
Router(config)# ip route 2.0.0.0 255.0.0.0 f0/0
```

#### Default Route

##### PC1

```
Router(config)# ip route 0.0.0.0 0.0.0.0 f0/0
```

##### R1

```
Router(config)# ip route 0.0.0.0 0.0.0.0 s1/1
```

##### R2

```
Router(config)# ip route 0.0.0.0 0.0.0.0 s1/0
```

##### PC2

```
Router(config)# ip route 0.0.0.0 0.0.0.0 f0/0
```
